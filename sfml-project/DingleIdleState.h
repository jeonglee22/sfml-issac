#pragma once
#include "MonsterState.h"
class DingleIdleState : public MonsterState
{
protected:
	float idleTimer;
	float idleDuration;

public:
	DingleIdleState();

	// MonsterState을(를) 통해 상속됨
	void Enter(Monster* monster) override;
	void Update(Monster* monster, float dt) override;
	void Exit(Monster* monster) override;
	std::string GetStateName() const override { return "DingleIdle"; }
};

