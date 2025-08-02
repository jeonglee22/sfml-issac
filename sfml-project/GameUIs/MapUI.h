#pragma once
#include "GameObject.h"

class Map;

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

	int mapIndex[11][11] = {};
	std::vector<MapType> mapType;
	std::vector<Map*> maps;
	bool mapCleared[11][11] = {false};

	int playerXIndex = 7;
	int beforePlayerXIndex = -1;
	int playerYIndex = 7;
	int beforePlayerYIndex = -1;

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
	void DrawIcons(sf::RenderWindow& window);

	void SetMapIndex(int index[][11]);
	void SetMapType(std::vector<MapType> types) { mapType = types; }
	void SetMaps(std::vector<Map*> maps) { this->maps = maps; }
	void SetMapCleared(bool b, int x, int y) { mapCleared[x][y] = b; }
	void SetPlayerXIndex(int x) { playerXIndex = x; }
	void SetPlayerYIndex(int y) { playerYIndex = y; }

	void LoadMapUITextures();
	std::string MatchTypeIcon(MapType ty);
};

