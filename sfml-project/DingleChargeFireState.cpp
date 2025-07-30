#include "stdafx.h"
#include "DingleChargeFireState.h"
#include "Monster.h"
#include "Dingle.h"

DingleChargeFireState::DingleChargeFireState()
	:chargeTimer(0.0f)
{
	chargeDuration = 1.3f;
}

void DingleChargeFireState::Enter(Monster* monster)
{
	chargeTimer = 0.0f;
	monster->SetVelocity(sf::Vector2f(0, 0));
	monster->GetAnimator().Play("animations/dingle_fire_charge.csv");
	monster->SetOrigin(Origins::MC);

}

void DingleChargeFireState::Update(Monster* monster, float dt)
{
	chargeTimer += dt;

	if (chargeTimer >= chargeDuration)
	{
		Dingle* dingle = static_cast<Dingle*>(monster);
		dingle->ChangeToFireState();
	}

}

void DingleChargeFireState::Exit(Monster* monster)
{
}
