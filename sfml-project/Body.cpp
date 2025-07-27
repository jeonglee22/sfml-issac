#include "stdafx.h"
#include "Body.h"

Body::Body(const std::string& name)
    : Monster(name, Monsters::Body)
{
}

void Body::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
    SetHP(120);
    SetSpeed(80.0f);
    SetDetectionRange(100.0f);
    SetSkillCooldown(5.0f);
    animator.Play("animations/body_front.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);
    canUseSkill = true;
    skillTimer = 0.0f;
    SetInitialState();
}

void Body::UseSkill()
{
}

void Body::SetInitialState()
{
    ChangeState(&wanderState);
}

sf::FloatRect Body::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return {
        bodyGlobalBounds.left + 25.f,
        bodyGlobalBounds.top + 25.f,
        18.f,
        18.f
    };
}
