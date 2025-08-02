#include "stdafx.h"
#include "WanderState.h"
#include "Monster.h"
#include <cmath>
#include "SpiderPatrolState.h"
#include "Mulligan.h"

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
    if (monster->GetMonsterType() == Monsters::Mulligan)
    {
        float distanceToPlayer = monster->GetDistanceToPlayer();
        if (distanceToPlayer <= monster->GetDetectionRange())
        {
            Mulligan* mulligan = static_cast<Mulligan*>(monster);
            mulligan->ChangeToFleeState();
            return;
        }
    }

    directionChangeTimer += dt;

    if (directionChangeTimer >= directionChangeInterval) {
        ChangeDirection();
        directionChangeTimer = 0.0f;

        if (monster->GetMonsterType() == Monsters::Body)
        {
            float x = targetDirection.x;
            float y = targetDirection.y;

            if (y == 0.0f)
            {
                if (x > 0)
                {
                    monster->GetAnimator().Play("animations/body_side.csv");
                    monster->SetScale({ 2.0f, 2.0f });
                }
                else
                {
                    monster->GetAnimator().Play("animations/body_side.csv");
                    monster->SetScale({ -2.0f, 2.0f });
                }
            }
            else
            {
                monster->GetAnimator().Play("animations/body_front.csv");
            }
        }
    }

    float wanderSpeed = 30.0f;
    if (monster->GetMonsterType() == Monsters::Body)
    {
        wanderSpeed = 100.0f;
    }
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
