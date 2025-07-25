#pragma once
#include "Scene.h"
#include "Map.h"

class SpriteGo;
class Isaac;
class Monster;
class HitBox;
class Door;
class Map;

class SceneGame : public Scene
{
protected:
	std::vector<Map*> maps;
	std::vector<SpriteGo*> mapSprites;

	Isaac* isaac = nullptr;
	std::vector<Monster*> monsters;

	sf::FloatRect currentMapSize;
	std::vector<HitBox*> boundary;

	sf::Vector2f offset = sf::Vector2f(140.f, 104.f);
	sf::Vector2f mapOffset;

	std::vector<Door*> doors;

	SpriteGo* shading;
	SpriteGo* overlay;

	int currentMapIndex = 0;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void EnemyCollosion();
	std::vector<Monster*> GetMonsters() { return monsters; }
	std::vector<HitBox*> GetMapBoundary() { return maps[currentMapIndex]->GetBoundary(); }
	std::vector<SpriteGo*> GetMapSprites() { return mapSprites; }
	std::vector<Door*> GetMapDoor() { return maps[currentMapIndex]->GetDoor(); }
	
	sf::View GetWorldView() { return worldView; }

	void GoNextMap();
};

