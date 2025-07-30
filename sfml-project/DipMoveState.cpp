#include "stdafx.h"
#include "DipMoveState.h"
#include "Monster.h"
#include "Dip.h"

std::random_device DipMoveState::rd;

DipMoveState::DipMoveState()
	: jumpSpeed(200.0f), gen(rd()), angleDist(0.0f, 2.0f * 3.14159f), distanceDist(80.0f, 150.0f)
{
}

void DipMoveState::Enter(Monster* monster)
{
    startPosition = monster->GetPosition();
    float angle = angleDist(gen);
    jumpDistance = distanceDist(gen);
    jumpDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
    targetPosition = startPosition + jumpDirection * jumpDistance;

    monster->GetAnimator().Play("animations/dip_move.csv");
    monster->SetOrigin(Origins::MC);
    monster->SetVelocity(jumpDirection * jumpSpeed);
}

void DipMoveState::Update(Monster* monster, float dt)
{
    sf::Vector2f currentPos = monster->GetPosition();
    sf::Vector2f diff = currentPos - targetPosition;
    float squaredDistance = diff.x * diff.x + diff.y * diff.y;

    // 목표 지점 근처에 도달하면 idle 상태로 전환
    if (squaredDistance < 30.0f * 30.0f) {
        monster->SetVelocity(sf::Vector2f(0, 0));
        Dip* dip = static_cast<Dip*>(monster);
        dip->ChangeToIdleState();
    }
}

void DipMoveState::Exit(Monster* monster)
{
	monster->SetVelocity(sf::Vector2f(0, 0));
}