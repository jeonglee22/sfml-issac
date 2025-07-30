#include "stdafx.h"
#include "PooterWanderState.h"
#include "Monster.h"
#include "Pooter.h"

PooterWanderState::PooterWanderState()
    : directionChangeTimer(0.0f)
{
    directionChangeInterval = 2.0f;
    ChangeDirection();
}

void PooterWanderState::Enter(Monster* monster)
{
    ChangeDirection();
    directionChangeTimer = 0.0f;
    monster->GetAnimator().Play("animations/pooter_idle.csv");
}

void PooterWanderState::Update(Monster* monster, float dt)
{
    Pooter* pooter = static_cast<Pooter*>(monster);
    pooter->UpdateProjectiles(dt);

    directionChangeTimer += dt;
    if (directionChangeTimer >= directionChangeInterval) {
        ChangeDirection();
        directionChangeTimer = 0.0f;
    }

    float detectionRange = monster->GetDetectionRange();
    float squaredDetectionRange = detectionRange * detectionRange;
    sf::Vector2f diff = monster->GetPlayerPosition() - monster->GetPosition();
    float squaredDistance = diff.x * diff.x + diff.y * diff.y;

    if (squaredDistance < squaredDetectionRange && monster->CanUseSkill())
    {
        monster->UseSkill();
        return;
    }

    float wanderSpeed = 30.0f;
    monster->SetVelocity(targetDirection * wanderSpeed);
}

void PooterWanderState::Exit(Monster* monster)
{
}

void PooterWanderState::ChangeDirection()
{
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    targetDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
    directionChangeInterval = 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
}
