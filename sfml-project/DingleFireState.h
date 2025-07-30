#pragma once
#include "MonsterState.h"
class DingleFireState : public MonsterState
{
protected:
	float fireTimer;
	float fireDuration = 0.4f;
	bool hasFire = false;

public:

	void Enter(Monster* monster) override;
	void Update(Monster* monster, float dt) override;
	void Exit(Monster* monster) override;
	std::string GetStateName() const override { return "DingleFire"; }


};

