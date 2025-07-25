#pragma once
#include "GameObject.h"
class MapUI : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId;

	std::unordered_map<std::string, sf::IntRect> mapIconRect;

	std::vector<sf::Sprite*> plates;
	std::vector<sf::Sprite*> rooms;
	std::vector<sf::Sprite*> icons;

	sf::Vector2f oneRoomSize;

	int mapIndex[15][15] = {};
	std::string mapType[15][15] = {};
	bool mapCleared[15][15] = {false};

	int playerXIndex = 7;
	int playerYIndex = 7;

public:
	MapUI(const std::string& textureId = "", const std::string & name = "");
	virtual ~MapUI() = default;

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
	void DrawPlates(sf::RenderWindow& window);
	void DrawRooms(sf::RenderWindow& window);

	void SetMapIndex(int index[][15]);
	void SetMapType(int index[][15]);
	void SetMapCleared(bool b, int x, int y) { mapCleared[x][y] = b; }
	void SetPlayerXIndex(int x) { playerXIndex = x; }
	void SetPlayerYIndex(int y) { playerYIndex = y; }

	void LoadMapUITextures();
};

