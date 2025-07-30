#include "stdafx.h"
#include "Dip.h"

Dip::Dip(const std::string& name)
	:Monster(name, Monsters::Dip)
{
}

sf::FloatRect Dip::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 15.f, bodyGlobalBounds.top + 15.f,
             bodyGlobalBounds.width - 30.f, bodyGlobalBounds.height - 30.f };
}

void Dip::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;

    SetHP(30);
    SetSpeed(12.0f);
    SetDetectionRange(120.0f);
    SetSkillCooldown(3.0f);

    animator.Play("animations/dip_idle.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;

    SetInitialState();
}

void Dip::UseSkill()
{
}

void Dip::SetInitialState()
{
    ChangeState(&idleState);
}
