#pragma once
#include "Scene.h"

class SpriteGo;

class SceneChange : public Scene
{
protected:
	SpriteGo* background;

	std::vector<SpriteGo*> stages;
	std::vector<SpriteGo*> clearStages;
	std::vector<SpriteGo*> stageConnects;
	sf::IntRect stageRect = {4,78,24,16};
	sf::IntRect clearRect = {100,46,24,16};
	sf::IntRect stageconnetRect = {0,51,32,4};
	
	SpriteGo* playerIcon;
	sf::IntRect playerIconRect = { 38,35,20,18 };

	SpriteGo* playerImage;

	int currentStage = 1;
	int maxStageCount = 5;

	float sceneDelayTimeMax = 2.f;
	float sceneDelayTime = 0.f;

	float iconMoveTime = 0.f;
	float iconMoveTimeMax = 2.f;

public:
	SceneChange();
	~SceneChange() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

