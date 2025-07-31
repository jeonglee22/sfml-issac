#pragma once
#include "Scene.h"

class Monster;
class SkillBible;
class Skill;
class SpriteGo;
class Isaac;
class HitBox;

class SceneDev2 : public Scene
{
protected:
	Monster* monster = nullptr;

	SkillBible* skillBible = nullptr;
	Skill* skill;
	SpriteGo* alter;
	Isaac* isaac;
	HitBox* hitBox;

	float movingTimeMax = 1.f;
	float movingTime = 0.f;
	float dir = -1.f;

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

