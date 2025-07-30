#include "stdafx.h"
#include "DingleFireState.h"
#include "Monster.h"
#include "Dingle.h"

void DingleFireState::Enter(Monster* monster)
{
	fireTimer = 0.0f;
	hasFire = false;
	monster->GetAnimator().Play("animations/dingle_fire.csv");
	monster->SetVelocity(sf::Vector2f(0, 0));

}

void DingleFireState::Update(Monster* monster, float dt)
{
    fireTimer += dt;

    if (!hasFire && fireTimer >= 0.3f)
    {
        Dingle* dingle = static_cast<Dingle*>(monster);

        sf::Vector2f playerPos = monster->GetPlayerPosition();
        sf::Vector2f horfPos = monster->GetPosition();
        sf::Vector2f direction = playerPos - horfPos;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0)
        {
            direction /= length;
        }

        dingle->FireTripleShot();
        hasFire = true;

        SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear fire 4.wav"));
    }

    if (fireTimer >= fireDuration)
    {
        Dingle* dingle = static_cast<Dingle*>(monster);
        dingle->ChangeToRushState();
    }
}

void DingleFireState::Exit(Monster* monster)
{
}
