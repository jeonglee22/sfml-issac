#include "stdafx.h"
#include "AttackFly.h"

AttackFly::AttackFly(const std::string& name)
    :Monster(name, Monsters::AttackFly)
{
}

void AttackFly::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;

    SetHP(50);
    SetSpeed(50.0f);
    SetDetectionRange(120.0f);
    SetSkillCooldown(4.0f);

    animator.Play("animations/attack_fly.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    SetInitialState();
}

void AttackFly::UseSkill()
{
}

void AttackFly::SetInitialState()
{
    ChangeState(&chaseState);
}

sf::FloatRect AttackFly::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 20.f, bodyGlobalBounds.top + 20.f, 3.f, 3.f };
}