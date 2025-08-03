#include "stdafx.h"
#include "MapUI.h"
#include "Map.h"
#include "rapidcsv.h"

MapUI::MapUI(const std::string& textureId, const std::string& name)
	: texId(textureId), GameObject(name)
{
}

void MapUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void MapUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void MapUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void MapUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void MapUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void MapUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	SetOrigin(Origins::MC);
}

void MapUI::Release()
{
	plates.clear();
	rooms.clear();
	icons.clear();
}

void MapUI::Reset()
{
	LoadMapUITextures();

	body.setTexture(TEXTURE_MGR.Get(texId));
	body.setTextureRect({0,0,55,49});
	Utils::SetOrigin(body, originPreset);

	for (int i = 0; i < 121; i++)
	{
		plates.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId), mapIconRect["plate"]));
		plates[i]->setScale({ 2.f,2.f });
		plates[i]->setOrigin(plates[i]->getLocalBounds().getSize() * 0.5f);

		rooms.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId), mapIconRect["dark5"]));
		rooms[i]->setScale({ 2.5f,2.5f });
		rooms[i]->setOrigin(rooms[i]->getLocalBounds().getSize() * 0.5f);

		icons.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId)));
		int yIndex = i / 11;
		int xIndex = i % 11;
		int index = mapIndex[yIndex][xIndex];
		if (index != -1 && index != 99)
		{
			MapType ty = mapType[index];
			std::string name = MatchTypeIcon(ty);
			icons[i]->setTextureRect(mapIconRect[name]);
		}
		else
		{
			icons[i]->setTextureRect(mapIconRect["empty"]);
		}
		icons[i]->setScale({ 2.f,2.f });
		icons[i]->setOrigin(icons[i]->getLocalBounds().getSize() * 0.5f);

		mapStatus[i / 11][i % 11] = Status::None;
	}

	mapStatus[playerYIndex][playerXIndex] = Status::Current;
	oneRoomSize = rooms[0]->getGlobalBounds().getSize();

	beforePlayerXIndex = -1;
	beforePlayerYIndex = -1;
}

void MapUI::Update(float dt)
{
	if(playerXIndex != beforePlayerXIndex || playerYIndex != beforePlayerYIndex)
	{
		for (int i = -2; i < 3; i++)
		{
			for (int j = -2; j < 3; j++)
			{
				int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 10);
				int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 10);
				int index = mapIndex[yIndex][xIndex];
				if (index != -1 && index != 99)
				{
					plates[yIndex * 11 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
					rooms[yIndex * 11 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
					icons[yIndex * 11 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
				}
			}
		}
		ChangeCurrentRoomVisit(playerYIndex, playerXIndex);
		if(mapIndex[playerYIndex][playerXIndex] != mapIndex[beforePlayerYIndex][beforePlayerXIndex])
		{
			//ChangeCurrentRoomVisit(playerYIndex, playerXIndex);
			if (beforePlayerXIndex != -1 && beforePlayerYIndex != -1)
			{
				ChangeBeforeRoomClear(beforePlayerYIndex, beforePlayerXIndex);
			}
		}
		beforePlayerXIndex = playerXIndex;
		beforePlayerYIndex = playerYIndex;
	}
}

void MapUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if(plates.size() > 0)
	{
		DrawPlates(window);
		DrawRooms(window);
		DrawIcons(window);
	}
}

void MapUI::DrawPlates(sf::RenderWindow& window)
{
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 10);
			int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 10);
			int index = mapIndex[yIndex][xIndex];
			if (index != -1 && mapStatus[yIndex][xIndex] > Status::None)
			{
				window.draw(*plates[yIndex * 11 + xIndex]);
			}
		}
	}
}

void MapUI::DrawRooms(sf::RenderWindow& window)
{
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 10);
			int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 10);
			int index = mapIndex[yIndex][xIndex];
			if (index != -1 && mapStatus[yIndex][xIndex] > Status::None)
			{
				window.draw(*rooms[yIndex * 11 + xIndex]);
			}
		}
	}
}

void MapUI::DrawIcons(sf::RenderWindow& window)
{
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
		{
			int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 10);
			int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 10);
			int index = mapIndex[yIndex][xIndex];
			if (index != -1 && index != 99 && mapStatus[yIndex][xIndex] > Status::None)
			{
				window.draw(*icons[11 * yIndex + xIndex]);
			}
		}
	}
}

void MapUI::SetMapIndex(int index[][11])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mapIndex[i][j] = index[i][j];
		}
	}
}

void MapUI::LoadMapUITextures()
{
	std::string filePath = "graphics/minimap.csv";
	
	rapidcsv::Document doc(filePath);

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		sf::IntRect rect = {std::stoi(row[1]),std::stoi(row[2]),std::stoi(row[3]) ,std::stoi(row[4]) };
		mapIconRect.insert({ row[0], rect });
	}
}

std::string MapUI::MatchTypeIcon(MapType ty)
{
	std::string iconName;

	switch (ty)
	{
	case MapType::Normal:
	case MapType::Special:
	case MapType::Large:
	case MapType::Rectangle:
	case MapType::Start:
		iconName = "empty";
		break;
	case MapType::Boss:
		iconName = "boss";
		break;
	case MapType::Hidden:
		iconName = "hidden";
		break;
	case MapType::Shop:
		iconName = "shop";
		break;
	case MapType::Treasure:
		iconName = "treasure";
		break;
	case MapType::Sacrifice:
		iconName = "sacrifice";
		break;
	default:
		break;
	}

	return iconName;
}

void MapUI::ChangeBeforeRoomClear(int x, int y)
{
	SetRoomStatus(x, y, mapType[mapIndex[x][y]], Status::Clear);
}

void MapUI::ChangeCurrentRoomVisit(int x, int y)
{
	SetRoomStatus(x, y, mapType[mapIndex[x][y]], Status::Current);
	if (mapType[mapIndex[x][y]] == MapType::Hidden)
		return;
	
	for (int i = 0; i < 4; i++)
	{
		int indexX = x + (i % 2 ? 0 : i - 1);
		int indexY = y + (i % 2 ? 2 - i : 0);
		int index = mapIndex[indexX][indexY];
		if (index != -1 && index != 99 && mapType[index] != MapType::Hidden && mapStatus[indexX][indexY] == Status::None)
			SetRoomStatus(indexX, indexY, mapType[index], Status::Dark);
	}
}

void MapUI::SetRoomStatus(int x, int y, MapType ty, Status status)
{
	int yIndex = maps[mapIndex[x][y]]->GetStageYIndex();
	int xIndex = maps[mapIndex[x][y]]->GetStageXIndex();
	switch (ty)
	{
	case MapType::Normal:
	case MapType::Start:
	case MapType::Boss:
	case MapType::Special:
	case MapType::Hidden:
	case MapType::Shop:
	case MapType::Treasure:
	case MapType::Sacrifice:
		mapStatus[x][y] = status;
		{
			switch (status)
			{
			case MapUI::Status::Dark:
				rooms[x * 11 + y]->setTextureRect(mapIconRect["dark5"]);
				break;
			case MapUI::Status::Current:
				rooms[x * 11 + y]->setTextureRect(mapIconRect["current5"]);
				break;
			case MapUI::Status::Clear:
				rooms[x * 11 + y]->setTextureRect(mapIconRect["clear5"]);
				break;
			default:
				break;
			}
		}
		break;
	case MapType::Large:
		SetLargeRoomStatus(yIndex, xIndex, status);
		break;
	case MapType::Rectangle:
		if (maps[mapIndex[x][y]]->GetIsRowMap())
		{
			SetRowRoomStatus(yIndex, xIndex, status);
		}
		else
		{
			SetColumnRoomStatus(yIndex, xIndex, status);
		}
		break;
	default:
		break;
	}
}

void MapUI::SetLargeRoomStatus(int x, int y, Status status)
{
	for (int i = 0; i < 4; i++)
	{
		int indexX = x + (i < 2 ? -1 : 0);
		int indexY = y + (i % 2 == 0 ? -1 : 0);
		int index = indexX * 11 + indexY;
		int numpad = 9 - (i < 2 ? i : i + 1 ) * 2;
		mapStatus[indexX][indexY] = status;
		switch (status)
		{
		case MapUI::Status::Dark:
			rooms[index]->setTextureRect(mapIconRect["dark" + std::to_string(numpad)]);
			break;
		case MapUI::Status::Current:
			rooms[index]->setTextureRect(mapIconRect["current" + std::to_string(numpad)]);
			break;
		case MapUI::Status::Clear:
			rooms[index]->setTextureRect(mapIconRect["clear" + std::to_string(numpad)]);
			break;
		default:
			break;
		}
	}
}

void MapUI::SetRowRoomStatus(int x, int y, Status status)
{
	mapStatus[x][y-1] = status;
	mapStatus[x][y] = status;
	switch (status)
	{
	case MapUI::Status::Dark:
		rooms[x * 11 + y - 1]->setTextureRect(mapIconRect["dark6"]);
		rooms[x * 11 + y]->setTextureRect(mapIconRect["dark4"]);
		break;
	case MapUI::Status::Current:
		rooms[x * 11 + y - 1]->setTextureRect(mapIconRect["current6"]);
		rooms[x * 11 + y]->setTextureRect(mapIconRect["current4"]);
		break;
	case MapUI::Status::Clear:
		rooms[x * 11 + y - 1]->setTextureRect(mapIconRect["clear6"]);
		rooms[x * 11 + y]->setTextureRect(mapIconRect["clear4"]);
		break;
	default:
		break;
	}
}

void MapUI::SetColumnRoomStatus(int x, int y, Status status)
{
	mapStatus[x-1][y] = status;
	mapStatus[x][y] = status;
	switch (status)
	{
	case MapUI::Status::Dark:
		rooms[(x - 1) * 11 + y]->setTextureRect(mapIconRect["dark8"]);
		rooms[x * 11 + y]->setTextureRect(mapIconRect["dark2"]);
		break;
	case MapUI::Status::Current:
		rooms[(x - 1) * 11 + y]->setTextureRect(mapIconRect["current8"]);
		rooms[x * 11 + y]->setTextureRect(mapIconRect["current2"]);
		break;
	case MapUI::Status::Clear:
		rooms[(x - 1) * 11 + y]->setTextureRect(mapIconRect["clear8"]);
		rooms[x * 11 + y]->setTextureRect(mapIconRect["clear2"]);
		break;
	default:
		break;
	}
}
