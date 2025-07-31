#include "stdafx.h"
#include "dingleSummonState.h"
#include "Monster.h"
#include "Dingle.h"

void dingleSummonState::Enter(Monster* monster)
{
    monster->GetAnimator().Play("animations/dingle_summon.csv");
    summonTimer = 0.0f;
}

void dingleSummonState::Update(Monster* monster, float dt)
{
    summonTimer += dt;
    if (summonTimer >= summonDuration)
    {
        Dingle* dingle = static_cast<Dingle*>(monster);
        dingle->ChangeToIdleState();
    }
}

void dingleSummonState::Exit(Monster* monster)
{
}
