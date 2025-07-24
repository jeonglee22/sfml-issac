#pragma once
#include "Scene.h"

class SpriteGo;

class SceneGame : public Scene
{
protected:
	std::vector<SpriteGo*> mapSprites;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;

	void LoadStageField(const std::string& filePath);
};

