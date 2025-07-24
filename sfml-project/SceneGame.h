#pragma once
#include "Scene.h"

class SpriteGo;
class Isaac;
class Monster;

class SceneGame : public Scene
{
protected:
	std::vector<SpriteGo*> mapSprites;
	Isaac* isaac = nullptr;
	std::vector<Monster*> monsters;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void LoadStageField(const std::string& filePath);
	void EnemyCollosion();
	std::vector<Monster*> GetMonsters() { return monsters; }
};

