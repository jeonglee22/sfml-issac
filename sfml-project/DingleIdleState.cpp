#include "stdafx.h"
#include "DingleIdleState.h"
#include "Monster.h"
#include "Dingle.h"

DingleIdleState::DingleIdleState()
    : idleTimer(0.0f)
{
    idleDuration = 2.0f;
}

void DingleIdleState::Enter(Monster* monster)
{
    idleTimer = 0.0f;
    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/dingle_idle.csv");
    monster->SetOrigin(Origins::MC);
}

void DingleIdleState::Update(Monster* monster, float dt)
{
    idleTimer += dt;

    if (idleTimer >= idleDuration)
    {
        Dingle* dingle = static_cast<Dingle*>(monster);
        dingle->ChangeToChargeFireState();
    }
}

void DingleIdleState::Exit(Monster* monster)
{
}
