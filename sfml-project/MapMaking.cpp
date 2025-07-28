#include "stdafx.h"
#include "rapidcsv.h"
#include "MapMaking.h"

int MapMaking::normalMapCount = 17;
int MapMaking::startMapCount = 3;

void MapMaking::MapRandomMaking(int mapCount)
{
	// Map Random Making algorithm
	// make mapIndex list, mapType list
	// mapIndex has value in -1 ~ mapCount-1
	// mapType list has value normal, shop, boss, hidden, ...
}

std::vector<Map*> MapMaking::SetMapInfo(std::vector<int> mapPos, int mapCount, std::vector<MapType> mapTypes)
{
	std::vector<Map*> maps;
	for (int i = 0; i < mapCount; i++)
	{
		maps.push_back(new Map());
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int mapIndex = mapPos[i * 15 +j];
			if (mapIndex != -1)
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

std::vector<Map*> MapMaking::SetMapInfo(std::string mapPosfile, int mapCount, std::string mapTypesfile)
{
	std::vector<int> mapPos;
	std::vector<MapType> mapTypes;

	rapidcsv::Document doc1(mapPosfile);
	rapidcsv::Document doc2(mapTypesfile);

	for (int i = 0; i < doc1.GetRowCount(); i++)
	{
		auto row = doc1.GetRow<int>(i);
		for (auto index : row)
			mapPos.push_back(index);
	}

	for (int i = 0; i < doc2.GetRowCount(); i++)
	{
		auto row = doc2.GetRow<int>(i);
		mapTypes.push_back((MapType)row[0]);
	}

	return SetMapInfo(mapPos, mapCount, mapTypes);
}

void MapMaking::GetMapInfo(std::string mapPosfile, int mapInfo[][15])
{
	rapidcsv::Document doc(mapPosfile);

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<int>(i);
		for (int j = 0; j < 15; j++)
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
		if (i > 0)
		{
			int xPos = maps[i]->GetStageXIndex();
			int yPos = maps[i]->GetStageYIndex();
			maps[i]->SetPosition({ maps[i]->GetMapSize().getSize().x * (xPos - 7) , maps[i]->GetMapSize().getSize().y * (yPos - 7) });
		}
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
