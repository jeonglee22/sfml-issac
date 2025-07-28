#pragma once
#include "Map.h"
#include "iomanip"

class SceneGame;

class MapMaking
{
public:
	enum class MapType
	{
		Normal,
		Start,
		Boss,
		Special,
		Hidden,
		Shop,
		Treasure,
	};

protected:
	static int normalMapCount;
	static int startMapCount;

public:
	static void InitMapSetting(int map[][11]);
	static sf::Vector2i MapRandomMaking(const int mapCount, int map[][11], std::vector<MapType> &mapTypes);
	static std::vector<Map*> SetMapInfo(int map[][11], int mapCount, std::vector<MapType> mapTypes);
	static void GetMapInfo(std::string mapPosfile, int mapInfo[][11]);
	static void SetMapConnection(std::vector<Map*> maps);

	static std::string PickRandomMapInPool(MapType mapTypes);

	static bool CheckNeighboorCount(const sf::Vector2i& pos, int map[][11]);

	static void PrintMap(int map[][11])
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				std::cout << std::right << std::setw(3) << map[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

