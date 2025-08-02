#include "stdafx.h"
#include "Monstro.h"
#include "SceneGame.h"

Monstro::Monstro(const std::string& name)
    : Monster(name, Monsters::Monstro)
{
}

sf::FloatRect Monstro::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return
    {
        bodyGlobalBounds.left + 40.f,
        bodyGlobalBounds.top + 140.f,
        bodyGlobalBounds.width - 80.f,
        bodyGlobalBounds.height - 140.f
    };
}

void Monstro::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 3;

    SetHP(2500);
    SetSpeed(100.0f);
    SetDetectionRange(800.0f);
    SetSkillCooldown(2.0f);

    animator.Play("animations/monstro_idle.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;

    jumpProgress = 0.0f;
    isInAir = false;

    for (auto* EnemyTear : EnemyTearsList)
    {
        EnemyTear->SetActive(false);
        EnemyTearsPool.push_back(EnemyTear);
    }
    EnemyTearsList.clear();

    SetInitialState();
}

void Monstro::UseSkill()
{
    FireCoughAttack();
}

void Monstro::SetInitialState()
{
    ChangeState(&idleState);
}

void Monstro::Update(float dt)
{
    Monster::Update(dt);
    UpdateTears(dt);
}

void Monstro::FireTear(const sf::Vector2f& direction)
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
    firePosition.y += 80.f;
    EnemyTear->Fire(firePosition, direction, tearsSpeed, tearsDamage, 800.f);
    EnemyTearsList.push_back(EnemyTear);
    scene->AddGameObject(EnemyTear);
}

void Monstro::FireBloodSplatter()
{
    const int shotCount = 8;
    for (int i = 0; i < shotCount; i++)
    {
        float angle = (2.0f * 3.14159f * i) / shotCount;
        sf::Vector2f direction(cos(angle), sin(angle));
        FireTear(direction);
    }

    SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/splatter 2.wav"));
}

void Monstro::FireCoughAttack()
{
    sf::Vector2f playerPos = GetPlayerPosition();
    sf::Vector2f monstroPos = GetPosition();
    sf::Vector2f baseDirection = playerPos - monstroPos;
    float length = std::sqrt(baseDirection.x * baseDirection.x + baseDirection.y * baseDirection.y);
    if (length > 0)
    {
        baseDirection /= length;
    }

    float spreadAngle = 0.5f;
    for (int i = 0; i < 5; i++)
    {
        float angle = spreadAngle * (i - 2) * 0.3f;  // -0.6 ~ 0.6 ¹üÀ§
        sf::Vector2f direction(
            baseDirection.x * cos(angle) - baseDirection.y * sin(angle),
            baseDirection.x * sin(angle) + baseDirection.y * cos(angle)
        );
        FireTear(direction);
    }

    SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear fire 4.wav"));
}

void Monstro::UpdateTears(float dt)
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

void Monstro::SetJumpTarget(const sf::Vector2f& target)
{
    jumpTarget = target;
    jumpStartPos = position;
}
