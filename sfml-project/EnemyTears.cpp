#include "stdafx.h"
#include "EnemyTears.h"
#include "SceneGame.h"
#include "Isaac.h"
#include "Obstacles.h"

EnemyTears::EnemyTears(const std::string& name)
    : GameObject(name), speed(150.0f), damage(1), distance(0.0f), maxRange(200.0f)
{
}

void EnemyTears::SetPosition(const sf::Vector2f& pos)
{
    GameObject::SetPosition(pos);
    sprite.setPosition(pos);
}

void EnemyTears::SetRotation(float rot)
{
    GameObject::SetRotation(rot);
    sprite.setRotation(rot);
}

void EnemyTears::SetScale(const sf::Vector2f& s)
{
    GameObject::SetScale(s);
    sprite.setScale(s);
}

void EnemyTears::SetOrigin(const sf::Vector2f& o)
{
    GameObject::SetOrigin(o);
    sprite.setOrigin(o);
}

void EnemyTears::SetOrigin(Origins preset)
{
    GameObject::SetOrigin(preset);
    if (preset != Origins::Custom)
    {
        Utils::SetOrigin(sprite, preset);
    }
}

void EnemyTears::Init()
{
    animator.SetTarget(&sprite);
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
}

void EnemyTears::Release()
{
}

void EnemyTears::Reset()
{
    animator.Play("animations/tears_idle.csv");

    crushTime = 0.0f;
    isCrush = false;
    damage = 1;
    distance = 0.0f;

    Utils::SetOrigin(sprite, Origins::MC);
    SetScale({ 1.5f, 1.5f });
}

void EnemyTears::Update(float dt)
{
    if (isCrush)
    {
        animator.Update(dt);
        crushTime += dt;

        if (crushTime >= crushMaxTime)
        {
            SetActive(false);
        }
        return;
    }

    animator.Update(dt);

    sf::Vector2f moveVector = velocity * dt;
    distance += Utils::Magnitude(moveVector);

    SetPosition(position + velocity * dt);
    hitBox.UpdateTransform(sprite, sprite.getLocalBounds());

    if (distance > maxRange)
    {
        StartCrush();
        return;
    }

    SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    if (scene)
    {
        for (auto sprite : scene->GetMapSprites())
        {
            if (sprite->GetName() == "rocks_basement" &&
                Utils::CheckCollision(hitBox.rect, ((Obstacles*)sprite)->GetHitBox()->rect))
            {
                StartCrush();
                SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
                return;
            }
        }

        for (auto boundary : scene->GetMapBoundary())
        {
            if (Utils::CheckCollision(hitBox.rect, boundary->rect))
            {
                StartCrush();
                SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
                return;
            }
        }
    }

    Hit();
}

void EnemyTears::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    hitBox.Draw(window);
}

void EnemyTears::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
    SetPosition(pos);
    direction = dir;
    velocity = dir * s;
    speed = s;
    damage = d;
    distance = 0.0f;
}

void EnemyTears::Hit()
{
    SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    if (!scene)
    {
        return;
    }

    Isaac* isaac = scene->GetIsaac();
    if (isaac)
    {
        sf::FloatRect projectileBounds = sprite.getGlobalBounds();
        sf::FloatRect isaacBounds = isaac->GetHitBoxHead().rect.getGlobalBounds();

        if (projectileBounds.intersects(isaacBounds))
        {
            isaac->TakeDamage(damage);
            StartCrush();
            SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
            return;
        }
    }
}

void EnemyTears::StartCrush()
{
    if (isCrush)
    {
        return;
    }

    animator.Play("animations/tears_boom.csv");

    isCrush = true;
    crushTime = 0.0f;
    damage = 0;

    velocity = { 0.f, 0.f };
}
