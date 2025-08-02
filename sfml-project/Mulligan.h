#pragma once
#include "Monster.h"
#include "WanderState.h"
#include "MulliganFleeState.h"
#include "MulliganDeathState.h"
#include "HitBox.h"


class Mulligan : public Monster
{
protected:
	WanderState wanderState;
	MulliganFleeState fleeState;
	MulliganDeathState deathState;

	sf::Sprite mulliganBody;
	sf::Sprite mulliganHead;

	bool isDeathSequence = false;

	Animator headAnimator;
	Animator bodyAnimator;

	HitBox headHitBox;
	HitBox bodyHitBox;

public:
	Mulligan(const std::string& name = "Mulligan");

	void Init() override;
	void SetPosition(const sf::Vector2f& pos) override;
	/*void SetScale(const sf::Vector2f& s) override;*/
	void Draw(sf::RenderWindow& window) override;
	void BodyAnimatorPlayEmpty() { bodyAnimator.Play("animations/empty.csv"); }

	void ChangeToFleeState() { ChangeState(&fleeState); }
	void ChangeToWanderState() { ChangeState(&wanderState); }
	void ChangeToDeathState() { ChangeState(&deathState); }

	void Reset() override;
	void Update(float dt) override;
	void UseSkill() override;
	void SetInitialState() override;

	void StartDeathSequence() { isDeathSequence = true; }
	bool IsInDeathSequence() const { return isDeathSequence; }

	sf::FloatRect GetHitBoxMonster() override;

};

