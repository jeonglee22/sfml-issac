#pragma once
#include "Monster.h"
#include "WanderState.h"

//class IdleState;
class SceneGame;

class Fly : public Monster
{
protected:
	WanderState wanderState;
	SceneGame* sceneGame;

public:
	Fly(const std::string& name = "fly");
	virtual ~Fly() override = default;

	void Reset() override;
	void UseSkill() override;
	//void Update(float dt) override;

	WanderState& GetWanderState() { return wanderState; }
	void SetInitialState() override;
	sf::FloatRect GetHitBoxMonster() override;
};

