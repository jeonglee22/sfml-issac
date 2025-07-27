#include "stdafx.h"
#include "Hopper.h"

Hopper::Hopper(const std::string& name)
	:Monster(name, Monsters::Hopper)
{
}

void Hopper::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
    SetHP(80);
    SetSpeed(100.0f);
    SetDetectionRange(150.0f);
    SetSkillCooldown(5.0f);
    animator.Play("animations/hopper_idle.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);
    canUseSkill = true;
    skillTimer = 0.0f;
    SetInitialState();
}

void Hopper::UseSkill()
{
    if (CanUseSkill())
    {
        ChangeToJumpState();
        StartSkillCooldown();
    }
}

void Hopper::SetInitialState()
{
    ChangeToIdleState();
}

sf::FloatRect Hopper::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 30.f, bodyGlobalBounds.top + 30.f, 15.f, 15.f };
}