#pragma once
#include "Monster.h"

class Mulligan : public Monster
{
protected:
	sf::Sprite mulliganBody;
	sf::Sprite mulliganHead;

	Animator bodyAnimator;
	Animator headAnimator;


public:
	Mulligan(const std::string& name = "Mulligan");

	//void Init() override;
	//void SetPosition(const sf::Vector2f& pos) override;
	//void Draw(sf::RenderWindow& window) override;


	void Reset() override;
	void UseSkill() override;
	void SetInitialState() override;

};

