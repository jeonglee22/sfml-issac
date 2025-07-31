#include "stdafx.h"
#include "Dingle.h"
#include "SceneGame.h"

Dingle::Dingle(const std::string& name)
	:Monster(name, Monsters::Dingle)
{
}

sf::FloatRect Dingle::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();

    return { bodyGlobalBounds.left + 32.f, bodyGlobalBounds.top + 32.f,
             bodyGlobalBounds.width - 64.f, bodyGlobalBounds.height - 64.f };
}

void Dingle::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 3;

    SetHP(3000);
    SetSpeed(30.0f);
    SetDetectionRange(500.0f);
    SetSkillCooldown(3.0f);

    animator.Play("animations/dingle_idle.csv");
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

void Dingle::UseSkill()
{
}

void Dingle::SetInitialState()
{
    ChangeState(&idleState);
}

void Dingle::FireTear(const sf::Vector2f& direction)
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

    EnemyTear->Fire(firePosition, direction, tearsSpeed, tearsDamage, 1000.f);
    EnemyTearsList.push_back(EnemyTear);

    scene->AddGameObject(EnemyTear);
}


void Dingle::FireTripleShot()
{
    sf::Vector2f playerPos = GetPlayerPosition();
    sf::Vector2f dinglePos = GetPosition();
    sf::Vector2f baseDirection = playerPos - dinglePos;

    float length = std::sqrt(baseDirection.x * baseDirection.x + baseDirection.y * baseDirection.y);
    if (length > 0)
    {
        baseDirection /= length;
    }

    float spreadAngle = 0.3f;

    std::vector<sf::Vector2f> directions = {
        baseDirection,
        sf::Vector2f(baseDirection.x * cos(spreadAngle) - baseDirection.y * sin(spreadAngle),
                     baseDirection.x * sin(spreadAngle) + baseDirection.y * cos(spreadAngle)),
        sf::Vector2f(baseDirection.x * cos(-spreadAngle) - baseDirection.y * sin(-spreadAngle),
                     baseDirection.x * sin(-spreadAngle) + baseDirection.y * cos(-spreadAngle))
    };

    for (auto& direction : directions)
    {
        FireTear(direction);
    }
}

void Dingle::UpdateTears(float dt)
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
