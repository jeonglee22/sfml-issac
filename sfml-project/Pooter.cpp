#include "stdafx.h"
#include "Pooter.h"
#include "PooterWanderState.h"
#include "PooterFireState.h"
#include "SceneGame.h"
#include "EnemyTears.h"

Pooter::Pooter(const std::string& name)
    : Monster(name, Monsters::Pooter)
{
}

void Pooter::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;

    SetHP(40);
    SetSpeed(30.0f);
    SetDetectionRange(120.0f);
    SetSkillCooldown(3.0f);

    animator.Play("animations/pooter_idle.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;

    for (auto* EnemyTear : EnemyTearsList)
    {
        EnemyTear->SetActive(false);
        EnemyTearsPool.push_back(EnemyTear);
    }
    EnemyTearsList.clear();

    SetInitialState();
}

void Pooter::UseSkill()
{
    if (CanUseSkill())
    {
        ChangeToFireState();
        StartSkillCooldown();
    }
}

void Pooter::SetInitialState()
{
    ChangeState(&wanderState);
}

sf::FloatRect Pooter::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 15.f, bodyGlobalBounds.top + 15.f,
             bodyGlobalBounds.width - 30.f, bodyGlobalBounds.height - 30.f };
}

void Pooter::FireProjectile(const sf::Vector2f& direction)
{
    SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    if (!scene)
    {
        return;
    }

    EnemyTears* EnemyTear = nullptr;

    if (EnemyTearsPool.empty())
    {
        EnemyTear = new EnemyTears();
        EnemyTear->Init();
    }
    else
    {
        EnemyTear = EnemyTearsPool.front();
        EnemyTearsPool.pop_front();
        EnemyTear->SetActive(true);
    }

    EnemyTear->Reset();

    sf::Vector2f firePosition = position;
    firePosition.y += 10.f;

    EnemyTear->Fire(firePosition, direction, tearsSpeed, tearsDamage);
    EnemyTearsList.push_back(EnemyTear);

    scene->AddGameObject(EnemyTear);
}

void Pooter::UpdateProjectiles(float dt)
{
    auto it = EnemyTearsList.begin();
    while (it != EnemyTearsList.end())
    {
        if ((*it)->GetActive())
        {
            (*it)->Update(dt);
        }

        if (!(*it)->GetActive())
        {
            EnemyTearsPool.push_back(*it);
            it = EnemyTearsList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}