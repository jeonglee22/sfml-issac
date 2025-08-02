#include "stdafx.h"
#include "MonstroSmallJumpState.h"
#include "Monster.h"
#include "Monstro.h"

MonstroSmallJumpState::MonstroSmallJumpState()
    : jumpTimer(0.0f)
{
    jumpDuration = 0.5f;
}

void MonstroSmallJumpState::Enter(Monster* monster)
{
    jumpTimer = 0.0f;
    monster->GetAnimator().Play("animations/monstro_small_jump.csv");

    Monstro* monstro = static_cast<Monstro*>(monster);

    sf::Vector2f playerPos = monster->GetPlayerPosition();
    sf::Vector2f currentPos = monster->GetPosition();
    sf::Vector2f direction = playerPos - currentPos;

    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 0)
    {
        direction /= distance;
    }

    sf::Vector2f jumpTarget = currentPos + direction * 150.0f;

    monstro->SetJumpTarget(jumpTarget);
    monstro->SetInAir(true);
    monstro->SetJumpProgress(0.0f);
}

void MonstroSmallJumpState::Update(Monster* monster, float dt)
{
    jumpTimer += dt;
    float progress = jumpTimer / jumpDuration;

    Monstro* monstro = static_cast<Monstro*>(monster);

    if (progress >= 1.0f)
    {
        progress = 1.0f;
        monstro->SetInAir(false);
        monstro->ChangeToIdleState();
    }

    monstro->SetJumpProgress(progress);

    sf::Vector2f startPos = monstro->GetJumpStartPos();
    sf::Vector2f targetPos = monstro->GetJumpTarget();

    sf::Vector2f currentPos;
    currentPos.x = startPos.x + (targetPos.x - startPos.x) * progress;
    currentPos.y = startPos.y + (targetPos.y - startPos.y) * progress;

    float jumpHeight = 50.0f;
    float verticalOffset = jumpHeight * sin(progress * 3.14159f);
    currentPos.y -= verticalOffset;

    monster->SetPosition(currentPos);
}

void MonstroSmallJumpState::Exit(Monster* monster)
{
}
