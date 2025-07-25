#include "stdafx.h"
#include "WanderState.h"
#include "Monster.h"
#include <cmath>
#include "SpiderPatrolState.h"

WanderState::WanderState()
    :directionChangeTimer(0.0f)
{
    directionChangeInterval = 2.0f;
    ChangeDirection();
}

void WanderState::Enter(Monster* monster)
{
    ChangeDirection();
    directionChangeTimer = 0.0f;
}

void WanderState::Update(Monster* monster, float dt)
{
    directionChangeTimer += dt;

    if (directionChangeTimer >= directionChangeInterval) {
        ChangeDirection();
        directionChangeTimer = 0.0f;
    }

    float wanderSpeed = 30.0f;
    monster->SetVelocity(targetDirection * wanderSpeed);

}

void WanderState::Exit(Monster* monster)
{
}

void WanderState::ChangeDirection()
{
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    targetDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
    directionChangeInterval = 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
}
