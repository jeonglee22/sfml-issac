#pragma once
#include "Monster.h"
#include "DipIdleState.h"
#include "DipMoveState.h"

class Dip : public Monster
{
protected:
	DipIdleState idleState;
	DipMoveState moveState;


public:
	Dip(const std::string& name = "Pooter");
	virtual ~Dip() override = default;

	sf::FloatRect GetHitBoxMonster() override;

	void ChangeToIdleState() { ChangeState(&idleState); }
	void ChangeToMoveState() { ChangeState(&moveState); }

	void Reset() override;
	void UseSkill() override;
	void SetInitialState() override;

	DipIdleState& GetWanderState() { return idleState; }
	DipMoveState& GetShootState() { return moveState; }
};

