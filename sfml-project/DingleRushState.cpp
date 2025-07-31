#include "stdafx.h"
#include "DingleRushState.h"
#include "Monster.h"
#include "Dingle.h"

void DingleRushState::Enter(Monster* monster)
{
	monster->GetAnimator().Play("animations/dingle_rush_charge.csv");
	chargeTimer = 0.0f;
	rushTimer = 0.0f;
    currentRush = 0;

    isExhausted = false;
    exhaustedTimer = 0.0f;
	isRush = false;
}

void DingleRushState::Update(Monster* monster, float dt)
{
    Dingle* dingle = static_cast<Dingle*>(monster);
    if (dingle->IsBouncing())
    {
        dingle->UpdateBounce(dt);
        return;
    }

    if (isExhausted)
    {
        exhaustedTimer += dt;

        if (exhaustedTimer >= exhaustedDuration)
        {
            isExhausted = false;
            exhaustedTimer = 0.0f;

            if (currentRush >= maxRushCount)
            {
                Dingle* dingle = static_cast<Dingle*>(monster);
                dingle->ChangeToSummonState();
            }
            else
            {
                monster->GetAnimator().Play("animations/dingle_rush_charge.csv");
            }
        }
        return;
    }


    if (!isRush)
    {
        chargeTimer += dt;

        if (chargeTimer >= chargeDuration)
        {
            isRush = true;
            chargeTimer = 0.0f;

            sf::Vector2f playerPos = monster->GetPlayerPosition();
            sf::Vector2f monsterPos = monster->GetPosition();
            sf::Vector2f direction = playerPos - monsterPos;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0)
            {
                direction /= length;
            }
            monster->SetVelocity(direction * 500.0f);
            monster->GetAnimator().Play("animations/dingle_rush.csv");
        }
    }
    if (isRush)
    {
        rushTimer += dt;
        if (rushTimer >= rushDuration)
        {
            currentRush++;
            rushTimer = 0.0f;
            isRush = false;
            monster->SetVelocity(sf::Vector2f(0, 0));

            isExhausted = true;
            exhaustedTimer = 0.0f;
            monster->GetAnimator().Play("animations/dingle_exhausted.csv");
        }
    }

}

void DingleRushState::Exit(Monster* monster)
{
}
