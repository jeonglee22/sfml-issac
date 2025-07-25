#pragma once
#include "GameObject.h"

class Spider;
class Fly;
class Obstacles;
class Spikes;
class Door;
class SpriteGo;
class HitBox;
class SceneGame;
class Item;

class Map : public GameObject
{
public:
	enum class mapType
	{
		None = 0,
		Normal,
		Gold,
		Boss,
		Store,
	};

protected:
	std::string filePath;
	sf::RectangleShape center;

	std::vector<SpriteGo*> allObjects;
	std::vector<Spider*> spiders;
	std::vector<Fly*> flys;
	std::vector<Obstacles*> obstacles;
	std::vector<Door*> doors;
	std::vector<Spikes*> spikes;
	std::vector<SpriteGo*> backgrounds;
	std::vector<HitBox*> boundary;
	std::vector<Item*> items;

	sf::FloatRect currentMapSize;

	SpriteGo* shading;
	SpriteGo* overlay;

	int spiderCount = 2;
	int flyCount = 2;

	SceneGame* sceneGame;

	bool isCleared = false;

public:
	Map(const std::string& filePath = "", const std::string & name = "");
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

	sf::FloatRect GetMapSize() const { return currentMapSize; }
	std::vector<HitBox*> GetBoundary() const { return boundary; }
	std::vector<Door*> GetDoor() const { return doors; }
	std::vector<SpriteGo*> GetObjects() const { return allObjects; }

	void AddSpider(const sf::Vector2f& pos);
	void AddFly(const sf::Vector2f& pos);
	void AddCoin(const sf::Vector2f& pos);
	void AddHeart(const sf::Vector2f& pos);
	void AddHalfHeart(const sf::Vector2f& pos);
	void AddBomb(const sf::Vector2f& pos);
	void AddKey(const sf::Vector2f& pos);
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
};

