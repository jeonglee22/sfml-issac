#include "stdafx.h"
#include "Bomb.h"
#include "SceneGame.h"
#include "Monster.h"
#include "SpriteGo.h"

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
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
}

void Bomb::Release()
{
}

void Bomb::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 2;

    explosionTime = 0.0f;
    explosionAnimationTime = 0.0f;
    wasExplosion = false;
    animator.Play("animations/bomb.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::BC);
}

void Bomb::Update(float dt)
{
    if (!wasExplosion)
    {
        explosionTime += dt;
        animator.Update(dt);

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
            bomb.setColor(sf::Color::White);

            Explosion();
        }
    }
    else
    {
        explosionAnimationTime += dt;
        animator.Update(dt);

       if (explosionAnimationTime >= explosionAnimationMaxTime)
        {
            animator.Play("animations/bombradius.csv");
            SetOrigin(Origins::BC);
        }
    }

    hitBox.UpdateTransform(bomb, bomb.getLocalBounds());
}



void Bomb::Draw(sf::RenderWindow& window)
{
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
            if (dist <= 80.f)
            {
                monster->TakeDamage(60);
            }
        }

        for (auto& obj : scene->GetMapSprites())
        {
            if (obj->GetName() == "rocks_basement" || obj->GetName() == "rocks_cracked")
            {
                float dist = Utils::Distance(position, obj->GetPosition());
                if (dist <= 80.f)
                {
                    obj->SetActive(false);
                }
            }
        }
    }
    
}
