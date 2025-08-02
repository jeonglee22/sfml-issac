#include "stdafx.h"
#include "MonstroFireState.h"
#include "Monster.h"
#include "Monstro.h"

MonstroFireState::MonstroFireState()
    : fireTimer(0.0f), hasFired(false)
{
    fireDuration = 1.0f;
}

void MonstroFireState::Enter(Monster* monster)
{
    fireTimer = 0.0f;
    hasFired = false;
    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/monstro_fire_charge.csv");
    monster->SetOrigin(Origins::MC);

    Monstro* monstro = static_cast<Monstro*>(monster);
    monstro->SetInAir(false);
}

void MonstroFireState::Update(Monster* monster, float dt)
{
    fireTimer += dt;

    if (!hasFired && fireTimer >= 1.0f)
    {
        monster->GetAnimator().Play("animations/monstro_fire.csv");

        Monstro* monstro = static_cast<Monstro*>(monster);
        monstro->FireCoughAttack();
        hasFired = true;
    }

    if (fireTimer >= fireDuration)
    {
        Monstro* monstro = static_cast<Monstro*>(monster);
        monstro->ChangeToIdleState();
    }
}

void MonstroFireState::Exit(Monster* monster)
{
}