#pragma once
#include "MonsterState.h"
class DipIdleState : public MonsterState
{
protected:
	float idleTimer = 0.0f;
	float idleDuration = 1.0f;

public:
	DipIdleState();

	void Enter(Monster* monster) override;
	void Update(Monster* monster, float dt) override;
	void Exit(Monster* monster) override;
	std::string GetStateName() const override { return "DipIdle"; }
};

