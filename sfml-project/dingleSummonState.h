#pragma once
#include "MonsterState.h"

class Dingle;

class DingleSummonState : public MonsterState
{
protected:
	float summonTimer = 0.0f;
	float summonDuration = 2.0f;

	bool hasSummoned = false;

public:

	// MonsterState을(를) 통해 상속됨
	void Enter(Monster* monster) override;

	void Update(Monster* monster, float dt) override;

	void Exit(Monster* monster) override;

	std::string GetStateName() const override { return "DingleSummon"; }

	void SummonOneDip(Dingle* dingle);

};

