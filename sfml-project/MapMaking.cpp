#include "stdafx.h"
#include "rapidcsv.h"
#include "MapMaking.h"

int MapMaking::normalMapCount = 17;
int MapMaking::startMapCount = 3;

void MapMaking::InitMapSetting(int map[][11])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			map[i][j] = -1;
			if (i == 0 || i == 10)
				map[i][j] = 99;
			if (j == 0 || j == 10)
				map[i][j] = 99;
		}
	}
}

sf::Vector2i MapMaking::MapRandomMaking(const int mapCount, int map[][11], std::vector<MapType>& mapTypes)
{
	// Map Random Making algorithm
	// make mapIndex list, mapType list
	// mapIndex has value in -1 ~ mapCount-1
	// mapType list has value normal, shop, boss, hidden, ...
	mapTypes.clear();
	InitMapSetting(map);
	mapTypes.push_back(MapType::Start);

	int startX = Utils::RandomRange(4, 7);
	int startY = Utils::RandomRange(4, 7);
	map[startX][startY] = 0;

	int mapNumber = 1;
	std::vector<sf::Vector2i> lastMaps;

	std::queue<sf::Vector2i> mapQueue;
	mapQueue.push({ startX, startY });
	while (mapQueue.size() != 0)
	{
		sf::Vector2i nowPos = mapQueue.front();
		mapQueue.pop();
		int addCount = 0;
		for (int i = 0; i < 4; i++)
		{
			int nextX = nowPos.x + (i % 2 == 0 ? i - 1 : 0 );
			int nextY = nowPos.y + (i % 2 != 0 ? 2 - i : 0 );

			if (map[nextX][nextY] != -1)
				continue;

			if (CheckNeighboorCount({ nextX, nextY }, map))
				continue;

			if (mapNumber >= mapCount)
				continue;

			if (Utils::RandomRange(0,2) == 1)
				continue;

			map[nextX][nextY] = mapNumber++;
			addCount++;
			mapQueue.push({ nextX, nextY });
			
		}
		if (addCount == 0)
		{
			if (std::find(lastMaps.begin(), lastMaps.end(), nowPos) == lastMaps.end() && 
				(nowPos.x != startX || nowPos.y != startY))
			{
				lastMaps.push_back(nowPos);
				mapTypes.push_back(MapType::Special);
			}
		}
		else
		{
			if (std::find(lastMaps.begin(), lastMaps.end(), nowPos) != lastMaps.end())
			{
				lastMaps.erase(std::find(lastMaps.begin(), lastMaps.end(), nowPos));
				mapTypes[map[nowPos.x][nowPos.y]] = MapType::Normal;
			}
			else if(nowPos.x != startX || nowPos.y != startY)
			{
				mapTypes.push_back(MapType::Normal);
			}
		}

		if (mapNumber < mapCount && mapQueue.size() == 0)
		{
			mapQueue.push({ startX, startY });
			if(lastMaps.size() != 0)
				mapQueue.push(lastMaps[Utils::RandomRange(0, lastMaps.size())]);
			/*mapTypes.erase(std::find(mapTypes.begin(), mapTypes.end(), mapTypes[map[lastMaps[0].x][lastMaps[0].y]]));
			lastMaps.erase(lastMaps.begin());*/
		}
	}
	PrintMap(map);
	for (auto last : lastMaps)
		std::cout << last.x << ", " << last.y << std::endl;
	return sf::Vector2i(startY, startX);
}

std::vector<Map*> MapMaking::SetMapInfo(int map[][11], int mapCount, std::vector<MapType> mapTypes)
{
	std::vector<Map*> maps;
	for (int i = 0; i < mapCount; i++)
	{
		maps.push_back(new Map());
	}

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int mapIndex = map[i][j];
			if (mapIndex != 99 && mapIndex != -1)
			{
				if (maps[mapIndex])
					delete maps[mapIndex];
				//maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex]), "map" + std::to_string(mapIndex));
				if (mapIndex == 0)
					maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex]), "start" + std::to_string(mapIndex));
				else
					maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex]), "map" + std::to_string(mapIndex));
				maps[mapIndex]->SetStageIndex(j, i);
			}
		}
	}
	maps[0]->SetCleared(true);

	return maps;
}

void MapMaking::GetMapInfo(std::string mapPosfile, int mapInfo[][11])
{
	rapidcsv::Document doc(mapPosfile);

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<int>(i);
		for (int j = 0; j < 11; j++)
			mapInfo[i][j] = row[j];
	}
}

void MapMaking::SetMapConnection(std::vector<Map*> maps)
{
	for (int i = 0; i < maps.size(); i++)
	{
		maps[i]->SetDoor();
		maps[i]->SetBoundary();
		maps[i]->AddGameObjectInScene();
		int xPos = maps[i]->GetStageXIndex();
		int yPos = maps[i]->GetStageYIndex();
		maps[i]->SetPosition({ maps[i]->GetMapSize().getSize().x * (xPos - 5) , maps[i]->GetMapSize().getSize().y * (yPos - 5) });
		maps[i]->SetActiveAll(false);
	}
	maps[0]->SetActiveAll(true);
	maps[0]->SetCleared(true);
}

std::string MapMaking::PickRandomMapInPool(MapType mapType)
{
	std::string fileName = "Mapfolder/";
	switch (mapType)
	{
	case MapMaking::MapType::Normal:
		fileName += "Normal/" + std::to_string(Utils::RandomRange(1, normalMapCount + 1)) + ".csv";
		break;
	case MapMaking::MapType::Start:
		fileName += "Start/" + std::to_string(Utils::RandomRange(1, startMapCount+1)) + ".csv";
		break;
	case MapMaking::MapType::Boss:
		fileName += "Boss/1.csv";
		break;
	case MapMaking::MapType::Hidden:
	case MapMaking::MapType::Special:
		fileName += "Normal/" + std::to_string(Utils::RandomRange(1, normalMapCount + 1)) + ".csv";
		break;
	case MapMaking::MapType::Shop:
		break;
	case MapMaking::MapType::Treasure:
		break;
	default:
		break;
	}

	return fileName;
}

bool MapMaking::CheckNeighboorCount(const sf::Vector2i& pos, int map[][11])
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		int neighboorX = pos.x + (i % 2 == 0 ? i - 1 : 0);
		int neighboorY = pos.y + (i % 2 != 0 ? 2 - i : 0);

		if (map[neighboorX][neighboorY] != -1 && map[neighboorX][neighboorY] != 99)
			count++;
	}
	return count > 1;
}
