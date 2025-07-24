#include "stdafx.h"
#include "SpiderPatrolState.h"
#include "Monster.h"
#include "Spider.h"
#include <cmath>

SpiderPatrolState::SpiderPatrolState()
    : directionChangeTimer(0.0f), pauseTimer(0.0f), isPausing(false)
{
    directionChangeInterval = 3.0f;
    pauseDuration = 1.0f;
    ChangeDirection();
}

void SpiderPatrolState::Enter(Monster* monster)
{
    ChangeDirection();
    directionChangeTimer = 0.0f;
    isPausing = false;

    monster->GetAnimator().Play("animations/spider_patrol.csv");
}

void SpiderPatrolState::Update(Monster* monster, float dt)
{
    directionChangeTimer += dt;

    if (isPausing)
    {
        pauseTimer += dt;
        monster->SetVelocity(sf::Vector2f(0, 0));

        if (pauseTimer >= pauseDuration)
        {
            isPausing = false;
            pauseTimer = 0.0f;
            ChangeDirection();
            directionChangeTimer = 0.0f;
        }
    }
    else
    {
        float patrolSpeed = 20.0f;
        monster->SetVelocity(targetDirection * patrolSpeed);

        if (directionChangeTimer >= directionChangeInterval)
        {
            isPausing = true;
        }
    }

    if (monster->GetDistanceToPlayer() < monster->GetDetectionRange() && monster->CanUseSkill())
    {
        monster->UseSkill();
    }
}

void SpiderPatrolState::Exit(Monster* monster)
{
}

void SpiderPatrolState::ChangeDirection()
{
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    targetDirection = sf::Vector2f(std::cos(angle), std::sin(angle));

    directionChangeInterval = 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
}

