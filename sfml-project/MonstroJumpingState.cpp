#include "stdafx.h"
#include "MonstroJumpingState.h"
#include "Monster.h"
#include "Monstro.h"

MonstroJumpingState::MonstroJumpingState()
    : jumpTimer(0.0f)
{
    jumpDuration = 1.0f;
}

void MonstroJumpingState::Enter(Monster* monster)
{
    jumpTimer = 0.0f;
    monster->GetAnimator().Play("animations/monstro_jump.csv");

    Monstro* monstro = static_cast<Monstro*>(monster);
    monstro->SetInAir(true);
    monstro->SetJumpProgress(0.0f);
}

void MonstroJumpingState::Update(Monster* monster, float dt)
{
    jumpTimer += dt;
    float progress = jumpTimer / jumpDuration;

    Monstro* monstro = static_cast<Monstro*>(monster);

    if (progress >= 1.0f)
    {
        progress = 1.0f;
        monstro->ChangeToLandingState();
    }

    monstro->SetJumpProgress(progress);

    sf::Vector2f startPos = monstro->GetJumpStartPos();
    sf::Vector2f targetPos = monstro->GetJumpTarget();

    sf::Vector2f currentPos;
    currentPos.x = startPos.x + (targetPos.x - startPos.x) * progress;
    currentPos.y = startPos.y + (targetPos.y - startPos.y) * progress;

    float jumpHeight = 2500.0f;
    float verticalOffset = jumpHeight * sin(progress * 3.14159f);
    currentPos.y -= verticalOffset;

    monster->SetPosition(currentPos);
}

void MonstroJumpingState::Exit(Monster* monster)
{
}
