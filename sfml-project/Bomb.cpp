    #include "stdafx.h"
#include "Bomb.h"
#include "SceneGame.h"
#include "Monster.h"
#include "SpriteGo.h"
#include "Door.h"
#include "Map.h"

Bomb::Bomb(const std::string& name)
{
}

void Bomb::SetPosition(const sf::Vector2f& pos)
{
    GameObject::SetPosition(pos);
    bomb.setPosition(pos);
}

void Bomb::SetRotation(float rot)
{
    GameObject::SetRotation(rot);
    bomb.setRotation(rot);
}

void Bomb::SetScale(const sf::Vector2f& s)
{
    GameObject::SetScale(s);
    bomb.setScale(s);
}

void Bomb::SetOrigin(Origins preset)
{
    GameObject::SetOrigin(preset);
    if (preset != Origins::Custom)
    {
        Utils::SetOrigin(bomb, preset);
    }
}

void Bomb::SetOrigin(const sf::Vector2f& o)
{
    GameObject::SetOrigin(o);
    bomb.setOrigin(o);
}

void Bomb::Init()
{
    animator.SetTarget(&bomb);
    radiusAnimator.SetTarget(&bombRadius);
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
}

void Bomb::Release()
{
}

void Bomb::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;

    explosionTime = 0.0f;
    explosionAnimationTime = 0.0f;
    wasExplosion = false;
    animator.Play("animations/bombInstall.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::BC);
}

void Bomb::Update(float dt)
{
    if (!wasExplosion)
    {
        explosionTime += dt;
        animator.Update(dt);
        radiusAnimator.Update(dt);

        if (explosionTime > explosionMaxTime - 2.0f)
        {
            float blinkTime = fmod(explosionTime, 0.2f);
            if (blinkTime < 0.1f)
            {
                bomb.setColor(sf::Color::White);
            }
            else
            {
                bomb.setColor(sf::Color::Red);
            }
        }

        if (explosionTime >= explosionMaxTime)
        {
            wasExplosion = true;

            animator.Play("animations/explosion.csv");
            SetOrigin(Origins::BC);
            bombRadius.setPosition(GetPosition().x, GetPosition().y);
            bombRadius.setScale({2.0f, 2.0f});
            radiusAnimator.Play("animations/bombradius.csv");
            bomb.setColor(sf::Color::White);

            Explosion();
        }
    }
    else
    {
        explosionAnimationTime += dt;
        animator.Update(dt);
        radiusAnimator.Update(dt);

       if (explosionAnimationTime >= explosionAnimationMaxTime)
       {
            animator.Play("animations/empty.csv");
            SetOrigin(Origins::MC);
       }
    }

    hitBox.UpdateTransform(bomb, bomb.getLocalBounds());
}

void Bomb::Draw(sf::RenderWindow& window)
{
    window.draw(bombRadius);
    window.draw(bomb);
    hitBox.Draw(window);
}

void Bomb::Explosion()
{
    SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    if (scene)
    {
        for (auto& monster : scene->GetMonsters())
        {
            if (!monster->GetActive() || monster->IsDead())
                continue;

            float dist = Utils::Distance(position, monster->GetPosition());
            if (dist <= explosionDistance)
            {
                monster->TakeDamage(60);
            }
        }

        for (auto& obj : scene->GetMapSprites())
        {
            if (obj->GetName() == "rocks_basement" || obj->GetName() == "rocks_cracked")
            {
                float dist = Utils::Distance(position, obj->GetPosition());
                if (dist <= explosionDistance)
                {
                    obj->SetActive(false);
                }
            }
        }

        for (auto& door : scene->GetMapDoor())
        {
            float dist = Utils::Distance(position, door->GetPosition());
            bool currentMapCleared = scene->GetCurrentMap()->GetCleared();
            if (door->GetDoorType() == MapType::Hidden && dist <= explosionDistance && currentMapCleared && door->GetDoorHidden())
            {
                door->SetDoorHidden(false);
                door->SetMapCleared(true);
                sf::Vector2f doorDirection = door->GetDoorDirection();
                std::cout << doorDirection.x << ", " << doorDirection.y << std::endl;
                int mapIndex = scene->GetMapIndex(scene->GetCurrentXIndex() + doorDirection.x, scene->GetCurrentYIndex() + doorDirection.y);
                SetHiddenNeighboorDoorOpen(scene->GetMap(mapIndex), doorDirection * -1.f);
            }
        }
    }
}

void Bomb::SetHiddenNeighboorDoorOpen(Map* hiddenMap, sf::Vector2f doorDir)
{
    std::vector<Door*> doors = hiddenMap->GetDoor();

    for (auto& door : doors)
    {
        if (door->GetDoorDirection() == doorDir)
        {
            door->SetDoorHidden(false);
            door->SetMapCleared(true);
        }
    }
}
