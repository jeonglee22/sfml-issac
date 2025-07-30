#pragma once
#include "MonsterState.h"

class DingleRushState : public MonsterState
{
protected:
	float chargeTimer = 0.0f;
	float chargeDuration = 1.0f;

	float rushTimer = 0.0f;
	float rushDuration = 1.0f;

	int maxRushCount = 3;
	int currentRush = 0.;
	bool isRush = false;


public:
	// MonsterState을(를) 통해 상속됨
	void Enter(Monster* monster) override;

	void Update(Monster* monster, float dt) override;

	void Exit(Monster* monster) override;

	std::string GetStateName() const override { return "DingleRush"; };

};

