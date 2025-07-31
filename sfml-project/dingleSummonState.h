#pragma once
#include "MonsterState.h"

class dingleSummonState : public MonsterState
{
protected:
	float summonTimer = 0.0f;
	float summonDuration = 2.0f;

public:

	// MonsterState��(��) ���� ��ӵ�
	void Enter(Monster* monster) override;

	void Update(Monster* monster, float dt) override;

	void Exit(Monster* monster) override;

	std::string GetStateName() const override { return "DingleSummon"; }

};

