#pragma once
#include "Scene.h"
#include "Map.h"

class SpriteGo;
class Isaac;
class Monster;
class Chest;
class HitBox;
class Door;
class Map;
class MapUI;
class ItemUI;
class HeartUI;
class SkillUI;
class Skill;
class TextGo;

class SceneGame : public Scene
{
protected:
	int mapIndex[11][11];
	std::vector<MapType> mapTypes;

	int beforeIndex = 0;
	int stageStartX = 7;
	int currentXIndex = stageStartX;
	int stageStartY = 7;
	int currentYIndex = stageStartY;
	sf::Vector2f nextSpawnPos;

	std::vector<Map *> maps;
	Isaac *isaac = nullptr;

	sf::Vector2f offset = sf::Vector2f(140.f, 104.f);
	sf::Vector2f mapOffset;
	sf::Vector2f nextMapViewStart;
	sf::Vector2f beforeMapView;

	sf::FloatRect currentMapSize;
	sf::FloatRect smallMapSize;

	std::vector<SpriteGo *> shadings;
	SpriteGo *overlay;
	SpriteGo *controls;

	MapUI *mapUI;
	ItemUI *itemUI;
	HeartUI *heartUI;
	SkillUI *skillUI;
	Skill *skill;

	int currentMapIndex = 0;

	bool isMapChanging = false;
	float mapChangeSpeed = 500.f;

	TextGo *FPS = nullptr;
	float FPSTime = 0.f;
	int frameCount = 0;

	float checkTimeMax = 0.3f;
	float checkTime = 0;

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow &window) override;

	void EnemyCollosion();

	std::vector<Monster *> GetMonsters() { return maps[currentMapIndex]->GetMonsters(); }
	std::vector<HitBox *> GetMapBoundary() { return maps[currentMapIndex]->GetBoundary(); }
	std::vector<HitBox *> GetMapTearBoundary() { return maps[currentMapIndex]->GetTearBoundary(); }
	std::vector<SpriteGo *> GetMapSprites() { return maps[currentMapIndex]->GetObjects(); }
	std::vector<Door *> GetMapDoor() { return maps[currentMapIndex]->GetDoor(); }
	std::vector<Chest *> GetChests() { return maps[currentMapIndex]->GetChests(); }

	Isaac* GetIsaac() { return isaac; }
	SkillUI* GetSkillUI() { return skillUI; }

	int GetMapIndex(int xPos, int yPos) { return mapIndex[yPos][xPos]; }
	std::vector<MapType> GetMapTypes() { return mapTypes; }
	sf::FloatRect GetSmallMapSize() { return smallMapSize; }
	Map* GetCurrentMap() { return maps[currentMapIndex]; }
	Map* GetMap(int index) { return maps[index]; }

	std::vector<int> GetNeighboorMapIndex(int x, int y);
	sf::Vector2i GetNeighboorMapIndexInRectangleMap(int x, int y);

	sf::View GetWorldView() { return worldView; }

	void AddSkillCooltimeAtClear();

	void ViewFollowing();

	void ChangeCurrentMapIndex();

	void SetItemUICount();

	void GoNextMap();
};
