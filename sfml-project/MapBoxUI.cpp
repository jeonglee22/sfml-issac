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

	SetGridRectValue();
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

void MapBoxUI::SetGridRectValue()
{
	sf::Vector2f topLeft(600.f - gridSize.x * 7.5f, 540.f - gridSize.y * 4.5f);
	for (int i = 0; i < (gridXcount - 1) * (gridYcount - 1); i++)
	{
		sf::IntRect rect;
		rect.top = topLeft.y + (i % (gridYcount - 1)) * 60;
		rect.left = topLeft.x + (i / (gridYcount - 1)) * 60;
		rect.width = 60;
		rect.height = 60;
		gridRect.push_back(rect);
	}
}

sf::Vector2f MapBoxUI::GetRectCenterHavePoint(const sf::Vector2f& point)
{
	for (auto rect : gridRect)
	{
		sf::RectangleShape shape;
		shape.setSize((sf::Vector2f)rect.getSize());
		shape.setPosition((sf::Vector2f)rect.getPosition());
		if (Utils::PointInTransformBounds(shape, shape.getLocalBounds(), point))
		{

		}
	}
	return sf::Vector2f(0.f,0.f);
}
