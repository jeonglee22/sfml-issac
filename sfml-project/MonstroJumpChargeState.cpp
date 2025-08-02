#include "stdafx.h"
#include "MonstroJumpChargeState.h"
#include "Monster.h"
#include "Monstro.h"

MonstroJumpChargeState::MonstroJumpChargeState()
    : chargeTimer(0.0f)
{
    chargeDuration = 0.5f;
}

void MonstroJumpChargeState::Enter(Monster* monster)
{
    chargeTimer = 0.0f;
    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/monstro_jump_charge.csv");
    monster->SetOrigin(Origins::MC);
}

void MonstroJumpChargeState::Update(Monster* monster, float dt)
{
    chargeTimer += dt;

    if (chargeTimer >= chargeDuration)
    {
        Monstro* monstro = static_cast<Monstro*>(monster);
        monstro->ChangeToJumpingState();
    }
}

void MonstroJumpChargeState::Exit(Monster* monster)
{
}
