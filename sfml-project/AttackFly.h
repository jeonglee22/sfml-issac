#pragma once
#include "Monster.h"
#include "ChaseState.h"


class AttackFly : public Monster
{
	protected:
		ChaseState chaseState;

	public:
		AttackFly(const std::string& name = "Attackfly");
		virtual ~AttackFly() override = default;

		void Reset() override;
		void UseSkill() override;

		ChaseState& GetChaseState() { return chaseState; }
		void SetInitialState() override;
		sf::FloatRect GetHitBoxMonster() override;
};

