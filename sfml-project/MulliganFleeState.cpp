#include "stdafx.h"
#include "MulliganFleeState.h"
#include "Monster.h"
#include "Mulligan.h"

MulliganFleeState::MulliganFleeState()
{
}

void MulliganFleeState::Enter(Monster* monster)
{
}

void MulliganFleeState::Update(Monster* monster, float dt)
{

    sf::Vector2f playerPos = monster->GetPlayerPosition();
    sf::Vector2f mulliganPos = monster->GetPosition();
    sf::Vector2f direction = mulliganPos - playerPos;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction /= length;
    }
    else
    {
        direction = sf::Vector2f(Utils::RandomRange(-1.0f, 1.0f), Utils::RandomRange(-1.0f, 1.0f));
    }

    float fleeSpeed = monster->GetSpeed();
    monster->SetVelocity(direction * fleeSpeed);

    float distanceToPlayer = monster->GetDistanceToPlayer();
    if (distanceToPlayer > monster->GetDetectionRange() * 1.5f)
    {
        Mulligan* mulligan = static_cast<Mulligan*>(monster);
        mulligan->ChangeToWanderState();
    }
}

void MulliganFleeState::Exit(Monster* monster)
{
}
