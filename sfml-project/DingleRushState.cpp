#include "stdafx.h"
#include "DingleRushState.h"
#include "Monster.h"
#include "Dingle.h"

void DingleRushState::Enter(Monster* monster)
{
	monster->GetAnimator().Play("animations/dingle_rush_charge.csv");
	chargeTimer = 0.0f;
	rushTimer = 0.0f;
	bool isRush = false;
}

void DingleRushState::Update(Monster* monster, float dt)
{
	if (currentRush == maxRushCount)
	{
		Dingle* dingle = static_cast<Dingle*>(monster);
		dingle->ChangeToIdleState();
	}

	if (!isRush)
	{
		chargeTimer += dt;
		if (chargeTimer >= chargeDuration)
		{
			isRush = true;

		}
	}

	if (isRush)
	{
		rushTimer += dt;
		if (rushTimer >= rushDuration)
		{
			currentRush += 1;
			rushTimer = 0.0f;

		}
	}

}

void DingleRushState::Exit(Monster* monster)
{
}
