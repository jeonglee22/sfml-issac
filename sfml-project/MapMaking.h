#pragma once
#include "Map.h"

class SceneGame;

class MapMaking
{
public:
	enum class MapType
	{
		Normal,
		Start,
		Boss,
		Hidden,
		Shop,
		Treasure,
	};

protected:
	static int normalMapCount;
	static int startMapCount;

public:
	static void MapRandomMaking(int mapCount);
	static std::vector<Map*> SetMapInfo(std::vector<int> mapPos, int mapCount, std::vector<MapType> mapTypes);
	static std::vector<Map*> SetMapInfo(std::string mapPosfile, int mapCount, std::string mapTypes);
	static void GetMapInfo(std::string mapPosfile, int mapInfo[][15]);
	static void SetMapConnection(std::vector<Map*> maps);

	static std::string PickRandomMapInPool(MapType mapTypes);
};

