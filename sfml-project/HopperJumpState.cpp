#include "stdafx.h"
#include "HopperJumpState.h"
#include "Monster.h"
#include "Hopper.h"
#include <cmath>

std::random_device HopperJumpState::rd;

HopperJumpState::HopperJumpState()
    : jumpSpeed(200.0f),
    gen(rd()),
    angleDist(0.0f, 2.0f * 3.14159f),
    distanceDist(80.0f, 150.0f)
{
}

void HopperJumpState::Enter(Monster* monster)
{
    startPosition = monster->GetPosition();

    float angle = angleDist(gen);
    jumpDistance = distanceDist(gen);
    jumpDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
    targetPosition = startPosition + jumpDirection * jumpDistance;

    monster->GetAnimator().Play("animations/hopper_jump.csv");
    monster->SetVelocity(jumpDirection * jumpSpeed);
}

void HopperJumpState::Update(Monster* monster, float dt)
{
    sf::Vector2f currentPos = monster->GetPosition();
    sf::Vector2f diff = currentPos - targetPosition;
    float squaredDistance = diff.x * diff.x + diff.y * diff.y;

    if (squaredDistance < 30.0f * 30.0f) {
        monster->SetVelocity(sf::Vector2f(0, 0));
        Hopper* hopper = static_cast<Hopper*>(monster);
        hopper->ChangeToIdleState();
    }
}

void HopperJumpState::Exit(Monster* monster)
{
    monster->SetVelocity(sf::Vector2f(0, 0));
}
