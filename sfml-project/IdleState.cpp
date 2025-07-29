#include "stdafx.h"
#include "IdleState.h"
#include "Monster.h"
#include "Horf.h"

void IdleState::Enter(Monster* monster)
{
    monster->GetAnimator().Play("animations/horf_idle.csv");
    monster->SetVelocity(sf::Vector2f(0, 0));
}

void IdleState::Update(Monster* monster, float dt)
{
    float detectionRange = monster->GetDetectionRange();
    float squaredDetectionRange = detectionRange * detectionRange;
    sf::Vector2f diff = monster->GetPlayerPosition() - monster->GetPosition();
    float squaredDistance = diff.x * diff.x + diff.y * diff.y;

    if (squaredDistance < squaredDetectionRange && monster->CanUseSkill())
    {
        monster->UseSkill();
    }
}

void IdleState::Exit(Monster* monster)
{
}
