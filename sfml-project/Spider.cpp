#include "stdafx.h"
#include "Spider.h"
#include "SpiderPatrolState.h"
#include "SpiderChargeState.h"
#include "SpiderJumpState.h"

Spider::Spider(const std::string& name) : Monster(name, Monsters::Spider)
{
}

void Spider::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 2;

    SetHP(130);
    SetSpeed(300.0f);
    SetDetectionRange(200.0f);
    SetSkillCooldown(3.0f);


    animator.Play("animations/spider_patrol.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;
    skillCooldown = 3.0f;

    SetInitialState();
}

void Spider::UseSkill()
{
    if (CanUseSkill())
    {
        ChangeState(&chargeState);
        StartSkillCooldown();
    }
}

void Spider::SetInitialState()
{
    ChangeState(&patrolState);
}

sf::FloatRect Spider::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 35.f, bodyGlobalBounds.top + 20.f, 20.f, 20.f };
}
