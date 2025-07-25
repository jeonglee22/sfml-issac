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

class Map : public GameObject
{
protected:
	std::string filePath;
	sf::RectangleShape center;

	std::vector<Spider*> spiders;
	std::vector<Fly*> flys;
	std::vector<Obstacles*> obstacles;
	std::vector<Door*> doors;
	std::vector<Spikes*> spikes;
	std::vector<SpriteGo*> backgrounds;
	std::vector<HitBox*> boundary;

	sf::FloatRect currentMapSize;

	SpriteGo* shading;
	SpriteGo* overlay;

	int spiderCount = 2;
	int flyCount = 2;

	SceneGame* sceneGame;

	int isMapPlaying = 0;

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

	sf::FloatRect GetMapSize() const { return currentMapSize; }
	std::vector<HitBox*> GetBoundary() const { return boundary; }
	std::vector<Door*> GetDoor() const { return doors; }

	void SetMapPlaying(int i) { isMapPlaying = 1; }

	void AddSpider(const sf::Vector2f& pos);
	void AddFly(const sf::Vector2f& pos);
	void SetDoor();
	void SetBoundary();

	void ClearSprites();

	void LoadStageField(const std::string& filePath);
	void CreateMatchedTypeGO(const std::vector<std::string> infos);
	void SpriteSetting(SpriteGo* sp, const std::vector<std::string> infos);

	void AddGameObjectInScene();
};

