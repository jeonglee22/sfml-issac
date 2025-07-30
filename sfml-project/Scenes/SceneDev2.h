#pragma once
#include "Scene.h"

class Monster;
class SkillBible;

class SceneDev2 : public Scene
{
protected:
	Monster* monster = nullptr;

	SkillBible* skillBible = nullptr;

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;

};

