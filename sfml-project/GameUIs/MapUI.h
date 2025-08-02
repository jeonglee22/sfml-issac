#pragma once
#include "GameObject.h"

class Map;

class MapUI : public GameObject
{
public:
	enum class Status
	{
		None = 0,
		Dark,
		Clear,
		Current,
		
	};

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
	Status mapStatus[11][11];

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
	void SetPlayerXIndex(int x) { playerXIndex = x; }
	void SetPlayerYIndex(int y) { playerYIndex = y; }
	void SetMapStatus(int x, int y, int status) { mapStatus[x][y] = (Status)status; }

	void LoadMapUITextures();
	std::string MatchTypeIcon(MapType ty);

	void ChangeBeforeRoomClear(int x, int y);
	void ChangeCurrentRoomVisit(int x, int y);

	void SetRoomStatus(int x, int y, MapType ty, Status status);
	void SetLargeRoomStatus(int x, int y, Status status);
	void SetRowRoomStatus(int x, int y, Status status);
	void SetColumnRoomStatus(int x, int y, Status status);
};

