#pragma once
#include "MonsterState.h"

class Monster;

class SpiderChargeState : public MonsterState
{
protected:
	float chargeTimer;
	float chargeDuration;
	sf::Vector2f targetPosition;

public:
	SpiderChargeState();

	void Enter(Monster* monster) override;
	void Update(Monster* monster, float dt) override;
	void Exit(Monster* monster) override;
	std::string GetStateName() const override { return "SpiderCharge"; }



};

