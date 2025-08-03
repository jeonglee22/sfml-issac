#pragma once
#include "Scene.h"

class SpriteGo;

class SceneStart : public Scene
{
protected:
	SpriteGo* background;

	SpriteGo* logo;
	sf::IntRect logoRect = { 0,280,480,100 };

	SpriteGo* pressStart;
	std::vector<sf::IntRect> pressRect =
	{
		{ 16,389,143,134 },
		{ 176,389,143,134 }
	};
	int startIndex = 0;

	SpriteGo* shading;
	SpriteGo* overlay;

	float pressChangeTimeMax = 0.2f;
	float pressChangeTime = 0.f;

	float rotationTimeMax = 0.5f;
	float rotationTime = 0.f;
	float rotationDir = 1.f;

	bool sceneChanging = false;

public:
	SceneStart();
	~SceneStart() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

