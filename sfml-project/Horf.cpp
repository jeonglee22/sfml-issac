#include "stdafx.h"
#include "Horf.h"
#include "IdleState.h"
#include "HorfFireState.h"

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
    SetDetectionRange(200.0f);
    SetSkillCooldown(3.0f);


    animator.Play("animations/horf_idle.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;
    skillCooldown = 3.0f;

    SetInitialState();
}

void Horf::UseSkill()
{
}

void Horf::SetInitialState()
{
    ChangeState(&idleState);
}

sf::FloatRect Horf::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 35.f, bodyGlobalBounds.top + 20.f, 20.f, 20.f };
}
