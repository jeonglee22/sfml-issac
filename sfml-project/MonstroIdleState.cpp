#include "stdafx.h"
#include "MonstroIdleState.h"
#include "Monster.h"
#include "Monstro.h"

MonstroIdleState::MonstroIdleState()
    : idleTimer(0.0f)
{
    idleDuration = 2.0f;  // 2ÃÊ ´ë±â
}

void MonstroIdleState::Enter(Monster* monster)
{
    idleTimer = 0.0f;
    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/monstro_idle.csv");
    monster->SetOrigin(Origins::MC);

    Monstro* monstro = static_cast<Monstro*>(monster);
    monstro->SetInAir(false);
}

void MonstroIdleState::Update(Monster* monster, float dt)
{
    idleTimer += dt;

    if (idleTimer >= idleDuration)
    {
        Monstro* monstro = static_cast<Monstro*>(monster);

        int randomChoice = Utils::RandomRange(1, 4);

        if (randomChoice == 1)
        {
            sf::Vector2f playerPos = monster->GetPlayerPosition();
            playerPos.y -= 130.f;
            monstro->SetJumpTarget(playerPos);
            monstro->ChangeToJumpChargeState();
        }
        else if (randomChoice == 2)
        {
            sf::Vector2f playerPos = monster->GetPlayerPosition();
            playerPos.y -= 130.f;
            monstro->SetJumpTarget(playerPos);
            monstro->ChangeToSmallJumpState();
        }
        else
        {
            monstro->ChangeToFireState();
        }
    }
}

void MonstroIdleState::Exit(Monster* monster)
{
}
