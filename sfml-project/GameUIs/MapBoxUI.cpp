#include "stdafx.h"
#include "MapBoxUI.h"
#include "SceneEditor.h"

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

	body.setSize({ 884.f, 572.f });
	SetOrigin({ 442.f, 286.f });

	for (int i = 0; i < obstacleGridXcount + obstacleGridYcount; i++)
	{
		obstacleGrid.push_back(sf::RectangleShape());
		if (i < obstacleGridXcount)
		{
			obstacleGrid[i].setSize({52.f * 13.f, 2.f});
		}
		else
		{
			obstacleGrid[i].setSize({ 2.f, 52.f * 7.f });
		}
		obstacleGrid[i].setOrigin(obstacleGrid[i].getSize() * 0.5f);
		obstacleGrid[i].setFillColor(sf::Color::Green);
	}

	for (int i = 0; i < backgroundGridXcount + backgroundGridYcount; i++)
	{
		backgroundGrid.push_back(sf::RectangleShape());
		if (i < backgroundGridXcount)
		{
			backgroundGrid[i].setSize({104.f * 8.5f, 2.f});
		}
		else
		{
			backgroundGrid[i].setSize({ 2.f, 104.f * 5.5f });
		}
		backgroundGrid[i].setOrigin(backgroundGrid[i].getSize() * 0.5f);
		backgroundGrid[i].setFillColor(sf::Color::Green);
	}
}

void MapBoxUI::Release()
{
}

void MapBoxUI::Reset()
{
	editorScene = (SceneEditor*)SCENE_MGR.GetCurrentScene();

	SetPosition({ (FRAMEWORK.GetWindowSizeF().x - 800.f) * 0.5f , FRAMEWORK.GetWindowSizeF().y * 0.5f});

	for (int i = 0; i < obstacleGridXcount + obstacleGridYcount; i++)
	{
		if (i < obstacleGridXcount)
		{
			obstacleGrid[i].setPosition(position + sf::Vector2f(0.f, (i - obstacleGridXcount * 0.5f + 0.5f) * obstacleGridSize.y));
		}
		else
		{
			obstacleGrid[i].setPosition(position + sf::Vector2f(((i-obstacleGridXcount) - obstacleGridYcount * 0.5f + 0.5f) * obstacleGridSize.x, 0.f));
		}
	}

	for (int i = 0; i < backgroundGridXcount + backgroundGridYcount; i++)
	{
		if (i < backgroundGridXcount)
		{
			float posdiff;
			if (i < 4)
				posdiff = 1.25f;
			else
				posdiff = -0.25f;
			sf::Vector2f localPos = sf::Vector2f(0.f, (i - backgroundGridXcount * 0.5f + posdiff) * backgroundGridSize.y);
			backgroundGrid[i].setPosition(position + localPos);
		}
		else
		{
			int yCount = i - backgroundGridXcount;
			sf::Vector2f localPos = sf::Vector2f((yCount - backgroundGridYcount * 0.5f + (yCount < 5 ? 0.75f : 0.25f)) * backgroundGridSize.x, 0.f);
			backgroundGrid[i].setPosition(position + localPos);
		}
	}

	SetGridRectValue();
}

void MapBoxUI::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		sortingLayer = SortingLayers::Background;
		sortingOrder = -100;
		for (auto grid : obstacleGrid)
		{
			grid.setPosition(editorScene->ScreenToWorld(editorScene->UiToScreen(grid.getPosition())));
		}
		isCheckingMap = true;
	}
	else if(InputMgr::GetKeyDown(sf::Keyboard::X))
	{
		sortingLayer = SortingLayers::UI;
		sortingOrder = 2;
		for (auto grid : obstacleGrid)
		{
			grid.setPosition(editorScene->ScreenToUi(editorScene->WorldToScreen(grid.getPosition())));
		}
		isCheckingMap = false;
	}

	std::string type = editorScene->GetCurrentType();
	if (type == "background")
	{
		currentType = Mode::Background;
	}
	else if (type == "obstacles")
	{
		currentType = Mode::obstacles;
	}
	else if (type == "enemies")
	{
		currentType = Mode::enemies;
	}
	else if (type == "additionals")
	{
		currentType = Mode::additionals;
	}
}

void MapBoxUI::Draw(sf::RenderWindow& window)
{
	//window.draw(body);
	if (currentType == Mode::obstacles || currentType == Mode::enemies || currentType == Mode::additionals)
	{
		for (int i = 0; i < obstacleGridXcount + obstacleGridYcount; i++)
		{
			window.draw(obstacleGrid[i]);
		}
	}
	if (currentType == Mode::Background)
	{
		for (int i = 0; i < backgroundGridXcount + backgroundGridYcount; i++)
		{
			window.draw(backgroundGrid[i]);
		}
	}
}

void MapBoxUI::SetGridRectValue()
{
	for (int i = 0; i < (obstacleGridXcount - 1) * (obstacleGridYcount - 1); i++)
	{
		sf::FloatRect rect;
		rect.left = topLeft.x + (i % (obstacleGridYcount - 1)) * obstacleGridSize.x;
		rect.top = topLeft.y + (i / (obstacleGridYcount - 1)) * obstacleGridSize.y;
		rect.width = obstacleGridSize.x;
		rect.height = obstacleGridSize.y;
		obstacleGridRect.push_back(rect);
	}

	for (int i = 0; i < (backgroundGridXcount - 1) * (backgroundGridYcount - 1); i++)
	{
		sf::FloatRect rect;
		int xCount = i / (backgroundGridYcount - 1);
		if (xCount == 3)
			continue;
		int yCount = i % (backgroundGridYcount - 1) + backgroundGridXcount;
		
		rect.left = backgroundGrid[yCount].getPosition().x;
		rect.top = backgroundGrid[xCount].getPosition().y;
		rect.width = backgroundGrid[yCount + 1].getPosition().x - rect.left;
		rect.height = backgroundGrid[xCount + 1].getPosition().y - rect.top;
		backgroundGridRect.push_back(rect);
	}
}

sf::RectangleShape MapBoxUI::GetRectHavePoint(const sf::Vector2f& point)
{
	for (auto rect : GetMapRect())
	{
		sf::RectangleShape shape;
		shape.setSize(rect.getSize());
		shape.setPosition(rect.getPosition());
		if (Utils::PointInTransformBounds(shape, shape.getLocalBounds(), point))
		{
			return shape;
		}
	}
	return sf::RectangleShape();
}

std::vector<sf::RectangleShape> MapBoxUI::GetMapGird()
{
	switch (currentType)
	{
	case MapBoxUI::Mode::Background:
		return backgroundGrid;
		break;
	case MapBoxUI::Mode::obstacles:
	case MapBoxUI::Mode::enemies:
	case MapBoxUI::Mode::additionals:
		return obstacleGrid;
		break;
	default:
		return std::vector<sf::RectangleShape>();
		break;
	}
}

std::vector<sf::FloatRect> MapBoxUI::GetMapRect()
{
	switch (currentType)
	{
	case MapBoxUI::Mode::Background:
		return backgroundGridRect;
		break;
	case MapBoxUI::Mode::obstacles:
	case MapBoxUI::Mode::additionals:
	case MapBoxUI::Mode::enemies:
		return obstacleGridRect;
		break;
	default:
		return std::vector<sf::FloatRect>();
		break;
	}

}
