#pragma once
#include "Monster.h"
#include "WanderState.h"
#include "HitBox.h"


class Mulligan : public Monster
{
protected:
	WanderState wanderState;

	sf::Sprite mulliganBody;
	sf::Sprite mulliganHead;

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


	void Reset() override;
	void Update(float dt) override;
	void UseSkill() override;
	void SetInitialState() override;

	sf::FloatRect GetHitBoxMonster() override;

};

