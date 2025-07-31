#pragma once
#include "Monster.h"
#include "DingleIdleState.h"
#include "DingleChargeFireState.h"
#include "DingleFireState.h"
#include "EnemyTears.h"
#include "DingleRushState.h"
#include "DingleSummonState.h"


class Dingle : public Monster
{
protected:
	DingleIdleState idleState;
	DingleChargeFireState chargeFireState;
	DingleFireState fireState;
	DingleRushState rushState;
	DingleSummonState summonState;

	std::list<EnemyTears*> EnemyTearsList;
	std::list<EnemyTears*> EnemyTearsPool;

	float tearsSpeed = 300.0f;
	int tearsDamage = 1;

	bool isBouncing = false;
	float bounceTimer = 0.0f;
	float bounceDuration = 0.2f;

public:
	Dingle(const std::string& name = "Dingle");
	virtual ~Dingle() override = default;

	sf::FloatRect GetHitBoxMonster() override;

	void ChangeToIdleState() { ChangeState(&idleState); }
	void ChangeToChargeFireState() { ChangeState(&chargeFireState); }
	void ChangeToFireState() { ChangeState(&fireState); }
	void ChangeToRushState() { ChangeState(&rushState); }
	void ChangeToSummonState() { ChangeState(&summonState); }

	void Reset() override;
	void UseSkill() override;
	void SetInitialState() override;

	void FireTear(const sf::Vector2f& direction);
	void FireTripleShot();
	void UpdateTears(float dt);

	void StartBounce()
	{
		isBouncing = true;
		bounceTimer = 0.0f;
	}

	bool IsBouncing() const
	{
		return isBouncing;
	}

	void UpdateBounce(float dt)
	{
		bounceTimer += dt;
		if (bounceTimer >= bounceDuration)
		{
			SetVelocity(sf::Vector2f(0, 0));
			isBouncing = false;
		}
	}

	const std::list<EnemyTears*>& GetTears() const { return EnemyTearsList; }
};

