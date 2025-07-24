#include "stdafx.h"
#include "MonsterState.h"
#include "SpiderJumpState.h"
#include "Monster.h"
#include "Spider.h"
#include "SpiderPatrolState.h"

SpiderJumpState::SpiderJumpState()
	:jumpSpeed(300.0f)
{
}

void SpiderJumpState::Enter(Monster* monster)
{
    startPosition = monster->GetPosition();
    targetPosition = monster->GetPlayerPosition();

    sf::Vector2f direction = targetPosition - startPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        jumpVelocity = (direction / distance) * jumpSpeed;
    }
    else {
        jumpVelocity = sf::Vector2f(jumpSpeed, 0);
    }

    monster->GetAnimator().Play("animations/spider_jump.csv");
    monster->SetVelocity(jumpVelocity);
}

void SpiderJumpState::Update(Monster* monster, float dt)
{
    sf::Vector2f currentPos = monster->GetPosition();
    sf::Vector2f diff = currentPos - targetPosition;
    float remainingDistance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (remainingDistance < 30.0f)
    {
        monster->SetVelocity(sf::Vector2f(0, 0));
        monster->ChangeState(&Spider::GetPatrolState());
    }
}

void SpiderJumpState::Exit(Monster* monster)
{
    monster->SetVelocity(sf::Vector2f(0, 0));
}