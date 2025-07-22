#include "stdafx.h"
#include "MapBoxUI.h"

MapBoxUI::MapBoxUI(const std::string& name)
	: GameObject(name)
{
}

void MapBoxUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void MapBoxUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void MapBoxUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void MapBoxUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void MapBoxUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void MapBoxUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 2;

	body.setSize({ 960.f, 540.f });
	SetOrigin({ 480.f, 270.f });

	for (int i = 0; i < gridXcount + gridYcount; i++)
	{
		grid.push_back(sf::RectangleShape());
		if (i < gridXcount)
		{
			grid[i].setSize({1080.f, 2.f});
		}
		else
		{
			grid[i].setSize({ 2.f, 660.f });
		}
		grid[i].setOrigin(grid[i].getSize() * 0.5f);
		grid[i].setFillColor(sf::Color::Green);
	}
}

void MapBoxUI::Release()
{
}

void MapBoxUI::Reset()
{
	SetPosition({ (FRAMEWORK.GetWindowSizeF().x - 600.f) * 0.5f , FRAMEWORK.GetWindowSizeF().y * 0.5f});
	for (int i = 0; i < gridXcount + gridYcount; i++)
	{
		if (i < gridXcount)
		{
			grid[i].setPosition(position + sf::Vector2f(0.f, (i - gridXcount * 0.5f + 0.5f) * gridSize.y));
		}
		else
		{
			grid[i].setPosition(position + sf::Vector2f(((i-gridXcount) - gridYcount * 0.5f + 0.5f) * gridSize.x, 0.f));
		}
	}
}

void MapBoxUI::Update(float dt)
{
}

void MapBoxUI::Draw(sf::RenderWindow& window)
{
	//window.draw(body);
	for (int i = 0; i < gridXcount + gridYcount; i++)
	{
		window.draw(grid[i]);
	}
}