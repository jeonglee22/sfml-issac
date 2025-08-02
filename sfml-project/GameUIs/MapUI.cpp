#include "stdafx.h"
#include "MapUI.h"
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
		rooms[i]->setScale({ 2.f,2.f });
		rooms[i]->setOrigin(rooms[i]->getLocalBounds().getSize() * 0.5f);

		mapCleared[i / 11][i % 11] = false;
	}

	SetMapCleared(true, playerXIndex, playerYIndex);
	oneRoomSize = rooms[0]->getGlobalBounds().getSize();

	beforePlayerXIndex = beforePlayerYIndex = -1;
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
				if (mapIndex[yIndex][xIndex] != -1 && mapIndex[yIndex][xIndex] != 99)
				{
					plates[yIndex * 11 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
					rooms[yIndex * 11 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
				}
			}
		}
		rooms[playerYIndex * 11 + playerXIndex]->setTexture(TEXTURE_MGR.Get(texId), true);
		rooms[playerYIndex * 11 + playerXIndex]->setTextureRect(mapIconRect["current5"]);
		if(beforePlayerXIndex != -1 && beforePlayerYIndex != -1)
		{
			rooms[beforePlayerYIndex * 11 + beforePlayerXIndex]->setTexture(TEXTURE_MGR.Get(texId), true);
			rooms[beforePlayerYIndex * 11 + beforePlayerXIndex]->setTextureRect(mapIconRect["clear5"]);
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
			if (mapIndex[yIndex][xIndex] != -1)
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
			if (mapIndex[yIndex][xIndex] != -1)
			{
				window.draw(*rooms[yIndex * 11 + xIndex]);
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

void MapUI::SetMapType(int index[][11])
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
