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

	LoadMapUITextures();

	SetMapCleared(true, 7, 7);
}

void MapUI::Release()
{
}

void MapUI::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	body.setTextureRect({0,0,55,49});

	for (int i = 0; i < 225; i++)
	{
		plates.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId), mapIconRect["plate"]));
		plates[i]->setScale({ 2.f,2.f });
		plates[i]->setOrigin(plates[i]->getLocalBounds().getSize());
		std::cout << plates[i]->getOrigin().x << ", " << plates[i]->getOrigin().y << std::endl;
		rooms.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId), mapIconRect["clear5"]));
		rooms[i]->setScale({ 2.f,2.f });
		rooms[i]->setOrigin(rooms[i]->getLocalBounds().getSize());
	}

	oneRoomSize = (sf::Vector2f) rooms[0]->getTextureRect().getSize() * 2.f;
	Utils::SetOrigin(body, originPreset);
}

void MapUI::Update(float dt)
{
	for (int i = -3; i < 4; i++)
	{
		for (int j = -3; j < 4; j++)
		{
			int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 14);
			int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 14);
			if (mapIndex[yIndex][xIndex] != -1)
			{
				plates[yIndex * 15 + xIndex]->setPosition(position + sf::Vector2f(j* oneRoomSize.x, i * oneRoomSize.y));
				rooms[yIndex * 15 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
			}
		}
	}
}

void MapUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	DrawPlates(window);
	DrawRooms(window);
}

void MapUI::DrawPlates(sf::RenderWindow& window)
{
	for (int i = -3; i < 4; i++)
	{
		for (int j = -3; j < 4; j++)
		{
			int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 14);
			int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 14);
			if (mapIndex[yIndex][xIndex] != -1)
			{
				window.draw(*plates[yIndex * 15 + xIndex]);
			}
		}
	}
}

void MapUI::DrawRooms(sf::RenderWindow& window)
{
	for (int i = -3; i < 4; i++)
	{
		for (int j = -3; j < 4; j++)
		{
			int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 14);
			int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 14);
			if (mapIndex[yIndex][xIndex] != -1)
			{
				window.draw(*rooms[yIndex * 15 + xIndex]);
			}
		}
	}
}

void MapUI::SetMapIndex(int index[][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			mapIndex[i][j] = index[i][j];
		}
	}
}

void MapUI::SetMapType(int index[][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
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

	std::cout << mapIconRect.size() << std::endl;
}
