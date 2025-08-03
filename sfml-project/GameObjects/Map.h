#pragma once
#include "GameObject.h"

class Obstacles;
class Spikes;
class Door;
class SpriteGo;
class HitBox;
class SceneGame;
class Monster;
class Item;
class Chest;

class Map : public GameObject
{
protected:
	std::string filePath;
	sf::RectangleShape center;

	std::vector<SpriteGo*> allObjects;
	std::vector<Monster*> monsters;
	std::vector<Obstacles*> obstacles;
	std::vector<Door*> doors;
	std::vector<Spikes*> spikes;
	std::vector<SpriteGo*> backgrounds;
	std::vector<HitBox*> boundary;
	std::vector<HitBox*> doorBoundary;
	std::vector<HitBox*> tearBoundary;
	std::vector<Item*> items;
	std::vector<Chest*> chests;

	sf::FloatRect currentMapRect;

	SpriteGo* shading;
	SpriteGo* overlay;

	MapType type;

	int spiderCount = 2;
	int flyCount = 2;
	int StageXPos;
	int StageYPos;

	SceneGame* sceneGame;

	bool isCleared = true;
	bool isRow = false;

public:
	Map(const std::string& filePath = "", const std::string& name = "", const MapType ty = MapType::None);
	virtual ~Map() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSpiderCount(int c) { spiderCount = c; }
	int GetSpiderCount() const { return spiderCount; }
	void SetFlyCount(int c) { flyCount = c; }
	int GetFlyCount() const { return flyCount; }
	void SetFilePath(int c) { flyCount = c; }
	int GetFilePath() const { return flyCount; }
	void SetCleared(bool b);
	bool GetCleared() const { return isCleared; }
	void SetType(MapType ty) { type = ty; }
	MapType GetType() const { return type; }
	void IsRowMap(bool b) { isRow = b; }
	bool GetIsRowMap() const { return isRow; }

	sf::FloatRect GetMapSize() const { return currentMapRect; }
	std::vector<HitBox*> GetBoundary() const { return boundary; }
	std::vector<HitBox*> GetTearBoundary() const { return tearBoundary; }
	std::vector<Door*> GetDoor() const { return doors; }
	std::vector<SpriteGo*> GetObjects() const { return allObjects; }
	std::vector<Monster*> GetMonsters() const { return monsters; }
	std::vector<Item*> GetItems() const { return items; }
	std::vector<Chest*> GetChests() const { return chests; }
	void AddItemToList(Item* item) { items.push_back(item); }
	void AddMonsterToList(Monster* monster) { monsters.push_back(monster); }

	void AddMonster(const sf::Vector2f& pos, const std::string& name);
	void AddItem(const sf::Vector2f& pos, const std::string& name);
	void AddChest(const sf::Vector2f& pos, const std::string& name);
	void SetDoor();
	void SetBoundary();

	void ClearSprites();

	void LoadStageField(const std::string& filePath);
	void CreateMatchedTypeGO(const std::vector<std::string> infos);
	void SpriteSetting(SpriteGo* sp, const std::vector<std::string> infos);

	void AddGameObjectInScene();
	void SetActiveAll(bool b);

	bool CheckAllEnemyDead();
	void DeleteEnemyAlreadyDead();
	void DeleteItemAlreadyGet();

	void SetStageIndex(int x, int y)
	{
		StageXPos = x;
		StageYPos = y;
	}
	int GetStageXIndex() { return StageXPos; }
	int GetStageYIndex() { return StageYPos; }
};
