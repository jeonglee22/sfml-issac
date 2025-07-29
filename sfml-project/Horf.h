#pragma once
#include "Monster.h"
#include "IdleState.h"
#include "HorfFireState.h"

class Horf : public Monster
{
protected:
	IdleState idleState;
	HorfFireState horfFireState;

public:
	Horf(const std::string& name = "Horf");
	virtual ~Horf() override = default;

	void Reset() override;
	void UseSkill() override;

	IdleState& GetIdleState() { return idleState; }
	HorfFireState& GetHorfFireState() { return horfFireState; }
	void SetInitialState() override;
	sf::FloatRect GetHitBoxMonster() override;

	void ChangeToHorfFireState() { ChangeState(&horfFireState); }
	void ChangeToIdleState() { ChangeState(&idleState); }
};

