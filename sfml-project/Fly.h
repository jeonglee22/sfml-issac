#pragma once
#include "Monster.h"

//class IdleState;
class WanderState;
class SceneGame;

class Fly : public Monster
{
protected:
	static WanderState wanderState;
	SceneGame* sceneGame;

public:
	Fly(const std::string& name = "fly");
	virtual ~Fly() override = default;

	void Reset() override;
	void UseSkill() override;
	//void Update(float dt) override;

	static WanderState& GetWanderState() { return wanderState; }
	void SetInitialState() override;
	sf::FloatRect GetHitBoxMonster() override;
};

