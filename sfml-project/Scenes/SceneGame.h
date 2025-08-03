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
class ExplainUI;
class PauseUI;
class Skill;
class TextGo;
class ItemAltar;
class GameOverUI;

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

	SpriteGo * shadings;
	SpriteGo *overlay;
	SpriteGo *controls;

	MapUI *mapUI;
	ItemUI *itemUI;
	HeartUI *heartUI;
	SkillUI *skillUI;
	ExplainUI* explainUI;
	PauseUI* pauseUI;
	GameOverUI* gameoverUI;

	int currentMapIndex = 0;

	bool isMapChanging = false;
	float mapChangeSpeed = 500.f;

	TextGo *FPS = nullptr;
	float FPSTime = 0.f;
	int frameCount = 0;

	float checkTimeMax = 0.3f;
	float checkTime = 0;

	SpriteGo* clearDoor;
	ItemAltar* clearAltar;
	sf::IntRect clearDoorclosedrect = { 16,80,32,32 };
	sf::IntRect clearDooropenrect = {16,16,32,32};
	bool isBossClear = false;
	bool isClearAlterPossed = false;
	float doorOpenTimeMax = 1.f;
	float doorOpenTime = 0.f;

	bool isCanGoNext = false;

	int stageIndex = 1;
	bool stageEnter = false;
	bool isStageMoving = false;

	float shownDelayMax = 1.f;
	float shownDelay = 0.f;
	float explainUIShowTimeMax = 1.f;
	float explainUIShowTime = 0.f;
	bool finishStageShow = false;
	bool finishShow = false;

	bool isGetSkill = false;
	bool isStop = false;

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
	int GetCurrentXIndex() const { return currentXIndex; }
	int GetCurrentYIndex() const { return currentYIndex; }
	std::vector<MapType> GetMapTypes() { return mapTypes; }
	sf::FloatRect GetSmallMapSize() { return smallMapSize; }
	Map* GetCurrentMap() { return maps[currentMapIndex]; }
	Map* GetMap(int index) { return maps[index]; }
	MapUI* GetMapUI() { return mapUI; }
	ExplainUI* GetExplainUI() { return explainUI; }

	bool GetGameStop() const { return isStop; }
	void SetGameStop(bool b) { isStop = b; }

	void SetIsGetSkill(bool b) { isGetSkill = b; }
	bool GetIsGetSkill() const { return isGetSkill; }

	std::vector<int> GetNeighboorMapIndex(int x, int y);
	sf::Vector2i GetNeighboorMapIndexInRectangleMap(int x, int y);

	sf::View GetWorldView() { return worldView; }
	sf::View GetUiView() { return uiView; }

	void AddSkillCooltimeAtClear();

	void ViewFollowing();

	void ChangeCurrentMapIndex();

	void SetItemUICount();

	void GoNextMap();
	void ResetStage();

	void ExplainUIMove(float dt);
	void ShowSkillExplainUI(float dt);
};
