#include "stdafx.h"
#include "rapidcsv.h"
#include "MapMaking.h"

int MapMaking::normalMapCount = 19;
int MapMaking::startMapCount = 10;
int MapMaking::treasureMapCount = 2;
int MapMaking::hiddenMapCount = 1;
int MapMaking::shopMapCount = 1;
int MapMaking::sacrificeMapCount = 1;
int MapMaking::bossMapCount = 1;
int MapMaking::largeMapCount = 1;
int MapMaking::rectangleMapCount = 1;

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

sf::Vector2i MapMaking::MapRandomMaking(const int mapCount, int map[][11], std::vector<MapType> &mapTypes)
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

	bool isHaveLarge = Utils::RandomRange(0.f, 1.f) <= 0.5f;

	bool isSquare = false;
	if (isHaveLarge)
	{
		isSquare = Utils::RandomRange(0.f, 1.f) <= 0.5f;
	}

	int mapNumber = 1;
	int largeMapNumber = -99;
	std::vector<sf::Vector2i> lastMaps;
	MapType largeMapType = MapType::None;

	std::queue<sf::Vector2i> mapQueue;
	mapQueue.push({startX, startY});
	while (mapQueue.size() != 0)
	{
		sf::Vector2i nowPos = mapQueue.front();
		mapQueue.pop();
		int addCount = 0;
		for (int i = 0; i < 4; i++)
		{
			int nextX = nowPos.x + (i % 2 == 0 ? i - 1 : 0);
			int nextY = nowPos.y + (i % 2 != 0 ? 2 - i : 0);

			if (map[nextX][nextY] != -1)
				continue;

			if (CheckNeighboorCount({nextX, nextY}, map))
				continue;

			if (mapNumber >= mapCount)
				continue;

			if (isHaveLarge && (Utils::RandomRange(0, 4) == 1))
			{
				if (AddLargeMap({nextX, nextY}, map, isSquare, mapNumber, mapQueue))
				{
					isHaveLarge = false;
					if (isSquare)
						largeMapType = MapType::Large;
					else
						largeMapType = MapType::Rectangle;
					largeMapNumber = mapNumber;
					mapNumber++;
					addCount++;
					continue;
				}
			}

			if (Utils::RandomRange(0, 2) == 1)
				continue;

			map[nextX][nextY] = mapNumber++;
			addCount++;
			mapQueue.push({nextX, nextY});
		}
		if (addCount == 0)
		{
			if (std::find(lastMaps.begin(), lastMaps.end(), nowPos) == lastMaps.end() &&
				(nowPos.x != startX || nowPos.y != startY))
			{
				if (map[nowPos.x][nowPos.y] != largeMapNumber)
				{
					lastMaps.push_back(nowPos);
					mapTypes.push_back(MapType::Special);
				}
				else
				{
					if (map[nowPos.x][nowPos.y] >= mapTypes.size())
						mapTypes.push_back(largeMapType);
				}
			}
		}
		else
		{
			if (std::find(lastMaps.begin(), lastMaps.end(), nowPos) != lastMaps.end())
			{
				lastMaps.erase(std::find(lastMaps.begin(), lastMaps.end(), nowPos));
				mapTypes[map[nowPos.x][nowPos.y]] = MapType::Normal;
			}
			else if (nowPos.x != startX || nowPos.y != startY)
			{
				if (map[nowPos.x][nowPos.y] >= mapTypes.size())
				{
					if (map[nowPos.x][nowPos.y] == largeMapNumber)
					{
						mapTypes.push_back(largeMapType);
					}
					else
					{
						mapTypes.push_back(MapType::Normal);
					}
				}
			}
		}

		if (mapNumber < mapCount && mapQueue.size() == 0)
		{
			mapQueue.push({startX, startY});
			if (lastMaps.size() != 0)
				mapQueue.push(lastMaps[Utils::RandomRange(0, lastMaps.size())]);
			/*mapTypes.erase(std::find(mapTypes.begin(), mapTypes.end(), mapTypes[map[lastMaps[0].x][lastMaps[0].y]]));
			lastMaps.erase(lastMaps.begin());*/
		}
	}

	if (lastMaps.size() < 3)
	{
		return MapRandomMaking(mapCount, map, mapTypes);
	}
	else
	{
		sf::Vector2i maxDistanceMap = lastMaps[0];
		for (auto map : lastMaps)
		{
			float distancefromMax = Utils::Distance((sf::Vector2f)maxDistanceMap, sf::Vector2f(startX, startY));
			if (Utils::Distance((sf::Vector2f)map, sf::Vector2f(startX, startY)) > distancefromMax)
				maxDistanceMap = map;
		}
		mapTypes[map[maxDistanceMap.x][maxDistanceMap.y]] = MapType::Boss;

		lastMaps.erase(std::find(lastMaps.begin(), lastMaps.end(), maxDistanceMap));
		sf::Vector2i randomMap = lastMaps[Utils::RandomRange(0, lastMaps.size())];
		mapTypes[map[randomMap.x][randomMap.y]] = MapType::Treasure;

		lastMaps.erase(std::find(lastMaps.begin(), lastMaps.end(), randomMap));
		randomMap = lastMaps[Utils::RandomRange(0, lastMaps.size())];
		if (Utils::RandomRange(0, 2) == 1)
		{
			mapTypes[map[randomMap.x][randomMap.y]] = MapType::Sacrifice;
		}
		else
		{
			mapTypes[map[randomMap.x][randomMap.y]] = MapType::Shop;
		}

		sf::Vector2i hiddenPos = FindHiddenPos(map);
		if (hiddenPos == sf::Vector2i{0, 0})
		{
			return MapRandomMaking(mapCount, map, mapTypes);
		}

		map[hiddenPos.x][hiddenPos.y] = mapNumber;
		mapTypes.push_back(MapType::Hidden);

		PrintMap(map);

		return sf::Vector2i(startY, startX);
	}
}

std::vector<Map *> MapMaking::SetMapInfo(int map[][11], int mapCount, std::vector<MapType> mapTypes)
{
	std::vector<Map *> maps;
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
				{
					delete maps[mapIndex];
					maps[mapIndex] = nullptr;
				}
				// maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex]), "map" + std::to_string(mapIndex));
				if (mapTypes[mapIndex] == MapType::Rectangle)
				{
					if (i > 1 && map[i - 1][j] != -1 && map[i - 1][j] != 99 && mapTypes[map[i - 1][j]] == MapType::Rectangle)
						maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex], false), ToString(mapTypes[mapIndex]), mapTypes[mapIndex]);
					else if (j > 1 && map[i][j - 1] != -1 && map[i][j - 1] != 99 && mapTypes[map[i][j - 1]] == MapType::Rectangle)
						maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex], true), ToString(mapTypes[mapIndex]), mapTypes[mapIndex]);
				}
				else
				{
					maps[mapIndex] = new Map(PickRandomMapInPool(mapTypes[mapIndex]), ToString(mapTypes[mapIndex]), mapTypes[mapIndex]);
				}
				if (maps[mapIndex])
				{
					maps[mapIndex]->SetStageIndex(j, i);
				}
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

void MapMaking::SetMapConnection(std::vector<Map *> maps)
{
	for (int i = 0; i < maps.size(); i++)
	{
		maps[i]->SetDoor();
		maps[i]->SetBoundary();
		maps[i]->AddGameObjectInScene();
		int xPos = maps[i]->GetStageXIndex();
		int yPos = maps[i]->GetStageYIndex();
		if (maps[i]->GetName() == "LargeMap")
		{
			sf::Vector2f pos;
			pos.x = maps[0]->GetMapSize().getSize().x * (xPos - 6);
			pos.y = maps[0]->GetMapSize().getSize().y * (yPos - 6);
			maps[i]->SetPosition(pos);
		}
		else if (maps[i]->GetName() == "RectangleMap")
		{
			sf::Vector2f pos;
			if (maps[i]->GetMapSize().getSize().x > maps[i]->GetMapSize().getSize().y)
			{
				pos.x = maps[0]->GetMapSize().getSize().x * (xPos - 6);
				pos.y = maps[0]->GetMapSize().getSize().y * (yPos - 5);
			}
			else
			{
				pos.x = maps[0]->GetMapSize().getSize().x * (xPos - 5);
				pos.y = maps[0]->GetMapSize().getSize().y * (yPos - 6);
			}
			maps[i]->SetPosition(pos);
		}
		else
		{
			maps[i]->SetPosition({maps[i]->GetMapSize().getSize().x * (xPos - 5), maps[i]->GetMapSize().getSize().y * (yPos - 5)});
		}
		maps[i]->SetActiveAll(false);
	}
	maps[0]->SetActiveAll(true);
	maps[0]->SetCleared(true);
}

std::string MapMaking::PickRandomMapInPool(MapType mapType, bool row)
{
	std::string fileName = "Mapfolder/";
	switch (mapType)
	{
	case MapType::Normal:
		fileName += "Normal/" + std::to_string(Utils::RandomRange(1, normalMapCount + 1)) + ".csv";
		break;
	case MapType::Start:
		fileName += "Start/" + std::to_string(Utils::RandomRange(1, startMapCount + 1)) + ".csv";
		break;
	case MapType::Boss:
		fileName += "Boss/" + std::to_string(Utils::RandomRange(1, bossMapCount + 1)) + ".csv";
		break;
	case MapType::Hidden:
		fileName += "Hidden/" + std::to_string(Utils::RandomRange(1, hiddenMapCount + 1)) + ".csv";
		break;
	case MapType::Special:
		fileName += "Normal/" + std::to_string(Utils::RandomRange(1, normalMapCount + 1)) + ".csv";
		break;
	case MapType::Shop:
		fileName += "Shop/" + std::to_string(Utils::RandomRange(1, shopMapCount + 1)) + ".csv";
		break;
	case MapType::Treasure:
		fileName += "Treasure/" + std::to_string(Utils::RandomRange(1, treasureMapCount + 1)) + ".csv";
		break;
	case MapType::Sacrifice:
		fileName += "Sacrifice/" + std::to_string(Utils::RandomRange(1, sacrificeMapCount + 1)) + ".csv";
		break;
	case MapType::Large:
		fileName += "Large/" + std::to_string(Utils::RandomRange(1, largeMapCount + 1)) + ".csv";
		break;
	case MapType::Rectangle:
		if (row)
			fileName += "Rectangle/Row/" + std::to_string(Utils::RandomRange(1, rectangleMapCount + 1)) + ".csv";
		else
			fileName += "Rectangle/Column/" + std::to_string(Utils::RandomRange(1, rectangleMapCount + 1)) + ".csv";
		break;
	default:
		break;
	}

	return fileName;
}

bool MapMaking::CheckNeighboorCount(const sf::Vector2i &pos, int map[][11])
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

bool MapMaking::AddLargeMap(const sf::Vector2i &pos, int map[][11], bool isSquare, int MapNumber, std::queue<sf::Vector2i> &queue)
{
	if (isSquare)
	{
		std::vector<sf::Vector2i> mapPos;

		for (int i = 0; i < 4; i++)
		{
			sf::Vector2i pos1 = pos;
			sf::Vector2i pos2 = i < 2 ? sf::Vector2i(pos.x, pos.y + 1) : sf::Vector2i(pos.x, pos.y - 1);
			sf::Vector2i pos3 = (i == 0 || i == 3) ? sf::Vector2i(pos.x - 1, pos.y) : sf::Vector2i(pos.x + 1, pos.y);
			sf::Vector2i pos4 = sf::Vector2i((i == 0 || i == 3) ? -1 : 1, i < 2 ? 1 : -1) + pos;

			if (map[pos1.x][pos1.y] != -1 || map[pos2.x][pos2.y] != -1 || map[pos3.x][pos3.y] != -1 || map[pos4.x][pos4.y] != -1)
				continue;

			mapPos.push_back(pos1);
			mapPos.push_back(pos2);
			mapPos.push_back(pos3);
			mapPos.push_back(pos4);
		}

		if (mapPos.size() == 0)
			return false;
		int resultPos = Utils::RandomRange(0, mapPos.size() / 4);

		for (int i = 0; i < 4; i++)
		{
			map[mapPos[resultPos * 4 + i].x][mapPos[resultPos * 4 + i].y] = MapNumber;
			queue.push(mapPos[resultPos * 4 + i]);
		}
	}
	else
	{
		std::vector<int> CanPos;
		std::vector<sf::Vector2i> mapPos;

		for (int i = 0; i < 4; i++)
		{
			sf::Vector2i pos1 = pos;
			sf::Vector2i pos2;
			pos2.x = pos.x + (i % 2 == 0 ? i - 1 : 0);
			pos2.y = pos.y + (i % 2 == 1 ? 2 - i : 0);

			if (map[pos1.x][pos1.y] != -1 || map[pos2.x][pos2.y] != -1)
				continue;

			mapPos.push_back(pos1);
			mapPos.push_back(pos2);
		}

		if (mapPos.size() == 0)
			return false;
		int resultPos = Utils::RandomRange(0, mapPos.size() / 2);

		for (int i = 0; i < 2; i++)
		{
			map[mapPos[resultPos * 2 + i].x][mapPos[resultPos * 2 + i].y] = MapNumber;
			queue.push(mapPos[resultPos * 2 + i]);
		}
	}

	return true;
}

std::string MapMaking::ToString(MapType ty)
{
	std::string str;
	switch (ty)
	{
	case MapType::Normal:
		str = "NormalMap";
		break;
	case MapType::Start:
		str = "StartlMap";
		break;
	case MapType::Boss:
		str = "BossMap";
		break;
	case MapType::Hidden:
		str = "HiddenMap";
		break;
	case MapType::Shop:
		str = "ShopMap";
		break;
	case MapType::Treasure:
		str = "TreasureMap";
		break;
	case MapType::Sacrifice:
		str = "SacrificeMap";
		break;
	case MapType::Large:
		str = "LargeMap";
		break;
	case MapType::Rectangle:
		str = "RectangleMap";
		break;
	default:
		break;
	}

	return str;
}

sf::Vector2i MapMaking::FindHiddenPos(int map[][11])
{
	sf::Vector2i hiddenPos;
	std::vector<sf::Vector2i> hiddenPosVector;

	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			int value = map[i][j];
			if (value == -1)
			{
				int count = GetNeighboorMapCount(map, { i,j });
				if (count > 2)
					hiddenPosVector.push_back({ i,j });
			}
		}
	}

	if (hiddenPosVector.size() > 0)
	{
		int index = Utils::RandomRange(0, hiddenPosVector.size());
		hiddenPos = hiddenPosVector[index];
	}
	return	hiddenPos;
}

int MapMaking::GetNeighboorMapCount(int map[][11], const sf::Vector2i& pos)
{
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		int val = map[pos.x + (i%2 ? 0 : 1 - i)][pos.y + (i % 2 ? 2-i : 0)];
		if (val != -1 && val != 99)
			count++;
	}

	return count;
}
