#include "stdafx.h"
#include "SpiderPatrolState.h"
#include "Monster.h"
#include "Spider.h"
#include <cmath>

std::random_device SpiderPatrolState::rd;

SpiderPatrolState::SpiderPatrolState()
    : directionChangeTimer(0.0f), pauseTimer(0.0f), isPausing(false), gen(rd()), angleDist(0.0f, 2.0f * 3.14159f), intervalDist(2.0f, 5.0f)
{
    directionChangeInterval = 1.0f;
    pauseDuration = 0.5f;
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
        float patrolSpeed = 40.0f;
        monster->SetVelocity(targetDirection * patrolSpeed);

        if (directionChangeTimer >= directionChangeInterval)
        {
            isPausing = true;
        }
    }

    float detectionRange = monster->GetDetectionRange();
    float squaredDetectionRange = detectionRange * detectionRange;

    sf::Vector2f diff = monster->GetPosition() - monster->GetPlayerPosition();
    float squaredDistance = diff.x * diff.y + diff.y * diff.y;

    if (squaredDistance < squaredDetectionRange && monster->CanUseSkill())
    {
        monster->UseSkill();
    }
}

void SpiderPatrolState::Exit(Monster* monster)
{
}

void SpiderPatrolState::ChangeDirection()
{
    float angle = angleDist(gen);
    targetDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
    directionChangeInterval = intervalDist(gen);
}

