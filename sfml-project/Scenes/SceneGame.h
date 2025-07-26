#pragma once
#include "Scene.h"
#include "Map.h"

class SpriteGo;
class Isaac;
class Monster;
class HitBox;
class Door;
class Map;
class MapUI;
class ItemUI;

class SceneGame : public Scene
{
protected:
	int mapIndex[15][15];
	int beforeIndex = 0;
	int stageStartX = 7;
	int currentXIndex = stageStartX;
	int stageStartY = 7;
	int currentYIndex = stageStartY;
	sf::Vector2f nextSpawnPos;

	std::vector<Map*> maps;
	std::vector<SpriteGo*> mapSprites;
	Isaac* isaac = nullptr;
	std::vector<Monster*> monsters;
	std::vector<HitBox*> boundary;
	std::vector<Door*> doors;

	sf::Vector2f offset = sf::Vector2f(140.f, 104.f);
	sf::Vector2f mapOffset;

	sf::FloatRect currentMapSize;

	std::vector<SpriteGo*> shadings;
	SpriteGo* overlay;

	MapUI* mapUI;
	ItemUI* itemUI;

	int currentMapIndex = 0;

	bool isMapChanging = false;
	float mapChangeSpeed = 500.f;

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
	std::vector<SpriteGo*> GetMapSprites() { return maps[currentMapIndex]->GetObjects(); }
	std::vector<Door*> GetMapDoor() { return maps[currentMapIndex]->GetDoor(); }

	std::vector<int> GetNeighboorMapIndex(int x, int y);
	
	sf::View GetWorldView() { return worldView; }
};

