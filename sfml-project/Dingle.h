#pragma once
#include "Monster.h"
#include "DingleIdleState.h"
#include "DingleChargeFireState.h"
#include "DingleFireState.h"
#include "EnemyTears.h"
#include "DingleRushState.h"


class Dingle : public Monster
{
protected:
	DingleIdleState idleState;
	DingleChargeFireState chargeFireState;
	DingleFireState fireState;
	DingleRushState rushState;

	std::list<EnemyTears*> EnemyTearsList;
	std::list<EnemyTears*> EnemyTearsPool;

	float tearsSpeed = 300.0f;
	int tearsDamage = 1;

public:
	Dingle(const std::string& name = "Dingle");
	virtual ~Dingle() override = default;

	sf::FloatRect GetHitBoxMonster() override;

	void ChangeToIdleState() { ChangeState(&idleState); }
	void ChangeToChargeFireState() { ChangeState(&chargeFireState); }
	void ChangeToFireState() { ChangeState(&fireState); }
	void ChangeToRushState() { ChangeState(&rushState); }

	void Reset() override;
	void UseSkill() override;
	void SetInitialState() override;

	void FireTear(const sf::Vector2f& direction);
	void FireTripleShot();
	void UpdateTears(float dt);

	const std::list<EnemyTears*>& GetTears() const { return EnemyTearsList; }
};

