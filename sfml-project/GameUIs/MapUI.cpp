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
	Utils::SetOrigin(body, originPreset);

	for (int i = 0; i < 225; i++)
	{
		plates.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId), mapIconRect["plate"]));
		plates[i]->setScale({ 2.f,2.f });
		plates[i]->setOrigin(plates[i]->getLocalBounds().getSize() * 0.5f);

		rooms.push_back(new sf::Sprite(TEXTURE_MGR.Get(texId), mapIconRect["clear5"]));
		rooms[i]->setScale({ 2.f,2.f });
		rooms[i]->setOrigin(rooms[i]->getLocalBounds().getSize() * 0.5f);
	}

	oneRoomSize = rooms[0]->getGlobalBounds().getSize();
}

void MapUI::Update(float dt)
{
	if(playerXIndex != beforePlayerXIndex || playerYIndex != beforePlayerYIndex)
	{
		for (int i = -2; i < 3; i++)
		{
			for (int j = -2; j < 3; j++)
			{
				int yIndex = (int)Utils::Clamp(playerYIndex + i, 0, 14);
				int xIndex = (int)Utils::Clamp(playerXIndex + j, 0, 14);
				if (mapIndex[yIndex][xIndex] != -1)
				{
					plates[yIndex * 15 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
					rooms[yIndex * 15 + xIndex]->setPosition(position + sf::Vector2f(j * oneRoomSize.x, i * oneRoomSize.y));
					//std::cout << rooms[yIndex * 15 + xIndex]->getPosition().x << ", " << rooms[yIndex * 15 + xIndex]->getPosition().y << std::endl;
					//std::cout << plates[yIndex * 15 + xIndex]->getPosition().x << ", " << plates[yIndex * 15 + xIndex]->getPosition().y << std::endl;
				}
			}
		}
		rooms[playerYIndex * 15 + playerXIndex]->setTexture(TEXTURE_MGR.Get(texId), true);
		rooms[playerYIndex * 15 + playerXIndex]->setTextureRect(mapIconRect["current5"]);
		if(beforePlayerXIndex != -1 && beforePlayerYIndex != -1)
		{
			rooms[beforePlayerYIndex * 15 + beforePlayerXIndex]->setTexture(TEXTURE_MGR.Get(texId), true);
			rooms[beforePlayerYIndex * 15 + beforePlayerXIndex]->setTextureRect(mapIconRect["clear5"]);
		}
		beforePlayerXIndex = playerXIndex;
		beforePlayerYIndex = playerYIndex;
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
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
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
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 3; j++)
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
