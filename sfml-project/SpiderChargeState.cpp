#include "stdafx.h"
#include "SpiderChargeState.h"
#include "Monster.h"
#include "Spider.h"
#include "SpiderJumpState.h"

SpiderChargeState::SpiderChargeState()
	:chargeTimer(0.0f), chargeDuration(1.0f)
{
}

void SpiderChargeState::Enter(Monster* monster)
{
    chargeTimer = 0.0f;

    targetPosition = monster->GetPlayerPosition();

    monster->SetVelocity(sf::Vector2f(0, 0));

    monster->GetAnimator().Play("animations/spider_charge.csv");
}

void SpiderChargeState::Update(Monster* monster, float dt)
{
    chargeTimer += dt;
    if (chargeTimer >= chargeDuration) {
        Spider* spider = static_cast<Spider*>(monster);
        spider->ChangeToJumpState();
    }
}

void SpiderChargeState::Exit(Monster* monster)
{
}
