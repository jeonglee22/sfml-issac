#include "stdafx.h"
#include "Horf.h"
#include "IdleState.h"
#include "HorfFireState.h"
#include "SceneGame.h"
#include "EnemyTears.h"

Horf::Horf(const std::string& name)
 :Monster(name, Monsters::Horf)
{
}

void Horf::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 2;

    SetHP(100);
    SetSpeed(0.0f);
    SetDetectionRange(300.0f);
    SetSkillCooldown(2.0f);


    animator.Play("animations/horf_idle.csv");
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

void Horf::UseSkill()
{
    if (CanUseSkill())
    {
        ChangeToFireState();
        StartSkillCooldown();
    }
}

void Horf::SetInitialState()
{
    ChangeState(&idleState);
}

sf::FloatRect Horf::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 10.f, bodyGlobalBounds.top + 10.f,  bodyGlobalBounds.width - 20.f, bodyGlobalBounds.height - 20.f };
}

void Horf::FireTear(const sf::Vector2f& direction)
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
    firePosition.y -= 10.f;

    EnemyTear->Fire(firePosition, direction, tearsSpeed, tearsDamage);
    EnemyTearsList.push_back(EnemyTear);

    scene->AddGameObject(EnemyTear);
}

void Horf::UpdateTears(float dt)
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
