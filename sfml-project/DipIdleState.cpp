#include "stdafx.h"
#include "DipIdleState.h"
#include "Monster.h"
#include "Dip.h"

DipIdleState::DipIdleState()
    : idleTimer(0.0f)
{
    idleDuration = 1.0f;
}

void DipIdleState::Enter(Monster* monster)
{
    idleTimer = 0.0f;
    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/dip_idle.csv");
    monster->SetOrigin(Origins::MC);
}


void DipIdleState::Update(Monster* monster, float dt)
{
    idleTimer += dt;

    if (idleTimer >= idleDuration)
    {
        Dip* dip = static_cast<Dip*>(monster);
        dip->ChangeToMoveState();
    }
}

void DipIdleState::Exit(Monster* monster)
{
}
