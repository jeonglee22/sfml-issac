#include "stdafx.h"
#include "MonstroLandingState.h"
#include "Monster.h"
#include "Monstro.h"

MonstroLandingState::MonstroLandingState()
    : landingTimer(0.0f), hasLanded(false)
{
    landingDuration = 1.0f;
}

void MonstroLandingState::Enter(Monster* monster)
{
    landingTimer = 0.0f;
    hasLanded = false;
    monster->GetAnimator().Play("animations/monstro_landing.csv");
    monster->SetVelocity(sf::Vector2f(0, 0));

    Monstro* monstro = static_cast<Monstro*>(monster);
    monstro->SetInAir(false);

 
    monster->SetPosition(monstro->GetJumpTarget());
}

void MonstroLandingState::Update(Monster* monster, float dt)
{
    landingTimer += dt;

    if (!hasLanded && landingTimer >= 0.2f)
    {
        Monstro* monstro = static_cast<Monstro*>(monster);
        monstro->FireBloodSplatter();
        hasLanded = true;
    }

    if (landingTimer >= landingDuration)
    {
        Monstro* monstro = static_cast<Monstro*>(monster);
        monstro->ChangeToIdleState();
    }
}

void MonstroLandingState::Exit(Monster* monster)
{
}
