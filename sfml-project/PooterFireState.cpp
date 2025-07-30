#include "stdafx.h"
#include "PooterFireState.h"
#include "Monster.h"
#include "Pooter.h"

void PooterFireState::Enter(Monster* monster)
{
    shootTimer = 0.0f;
    hasShot = false;
    monster->GetAnimator().Play("animations/pooter_fire.csv");
    monster->SetVelocity(sf::Vector2f(0, 0));
}

void PooterFireState::Update(Monster* monster, float dt)
{
    Pooter* pooter = static_cast<Pooter*>(monster);
    pooter->UpdateProjectiles(dt);

    shootTimer += dt;

    if (!hasShot && shootTimer >= 0.1f)
    {
        sf::Vector2f playerPos = monster->GetPlayerPosition();
        sf::Vector2f pooterPos = monster->GetPosition();
        sf::Vector2f direction = playerPos - pooterPos;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0)
        {
            direction /= length;
        }

        pooter->FireProjectile(direction);
        hasShot = true;

        SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear fire 4.wav"));
    }

    if (shootTimer >= shootDuration)
    {
        pooter->ChangeToWanderState();
    }
}

void PooterFireState::Exit(Monster* monster)
{
}
