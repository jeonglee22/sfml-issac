#include "stdafx.h"
#include "ChaseState.h"
#include "Monster.h"

ChaseState::ChaseState()
{
}

void ChaseState::Enter(Monster* monster)
{
    monster->GetAnimator().Play("animations/attack_fly.csv");
}
void ChaseState::Update(Monster* monster, float dt)
{
    SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/insect swarm.wav"));

    startPosition = monster->GetPosition();
    targetPosition = monster->GetPlayerPosition();
    targetPosition.y -= 30.0f;

    sf::Vector2f direction = targetPosition - startPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0)
    {
        direction = direction / distance;
   
        monster->SetVelocity(direction * chaseSpeed);
    }

}
void ChaseState::Exit(Monster* monster)
{
    monster->SetVelocity(sf::Vector2f(0, 0));

}