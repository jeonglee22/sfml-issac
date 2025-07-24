#pragma once
#include "Scene.h"

class SpriteGo;
class Isaac;
class Monster;
class HitBox;
class Door;

class SceneGame : public Scene
{
protected:
	std::vector<SpriteGo*> mapSprites;

	Isaac* isaac = nullptr;
	std::vector<Monster*> monsters;

	sf::FloatRect currentMapSize;
	std::vector<HitBox*> boundary;

	sf::Vector2f offset = sf::Vector2f(140.f, 104.f);
	sf::Vector2f mapOffset;

	std::vector<Door*> doors;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void LoadStageField(const std::string& filePath);
	void CreateMatchedTypeGO(const std::string& filepath, const std::string& name);

	void EnemyCollosion();
	std::vector<Monster*> GetMonsters() { return monsters; }

	std::vector<SpriteGo*> GetMapSprites() { return mapSprites; }

	void MakeBoundary();
	void MakeDoor();
	std::vector<HitBox*> GetMapBoundary() { return boundary; }
};

