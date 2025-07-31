#pragma once
#include "MonsterState.h"

class DipMoveState : public MonsterState
{
protected:
	sf::Vector2f jumpDirection;
	float jumpDistance;
	sf::Vector2f startPosition;
	sf::Vector2f targetPosition;
	float jumpSpeed;

	float moveTimer = 0.0f;
	float maxMoveTime = 2.0f;

	static std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> angleDist;
	std::uniform_real_distribution<float> distanceDist;

public:
	DipMoveState();

	// MonsterState을(를) 통해 상속됨
	void Enter(Monster* monster) override;
	void Update(Monster* monster, float dt) override;
	void Exit(Monster* monster) override;
	std::string GetStateName() const override { return "DipMove"; }

	void ChangeDirection();
};

