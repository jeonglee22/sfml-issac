#include "stdafx.h"
#include "EditBoxUI.h"
#include "rapidcsv.h"

EditBoxUI::EditBoxUI(const std::string& name)
	: GameObject(name)
{
}

void EditBoxUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void EditBoxUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void EditBoxUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void EditBoxUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void EditBoxUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void EditBoxUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 2;
	body.setSize({ 600.f, 1080.f });
	SetOrigin(Origins::MC);

	basementGroundId = "graphics/basement/01_basement.png";

	for(int i = 0; i< 3; i++)
	{
		typeButtons.push_back(new Button());
		typeButtons[i]->Init();
		typeButtons[i]->SetButtonRectSize({ 120.f, 30.f });
		typeButtons[i]->SetButtonRectColor(sf::Color::Black);
		typeButtons[i]->SetButtonRectOrigin({ 60.f, 15.f });
		typeButtons[i]->SetButtonRectOutlineColor(sf::Color::Black);
		typeButtons[i]->SetButtonRectOutlineThickness(3.f);
		typeButtons[i]->SetTextSize(25);
	}
}

void EditBoxUI::Release()
{
	//fileButton->Release();
}

void EditBoxUI::Reset()
{
	SetPosition({ 1920.f - 300.f, 540.f });

	for (int i = 0; i < 3; i++)
	{
		typeButtons[i]->Reset();
		typeButtons[i]->SetPosition(position + sf::Vector2f(-150.f + i * 150.f, -500.f));
		typeButtons[i]->SetTextPosition({ 0.f, -10.f });
		if (i == 0)
			typeButtons[i]->SetTextString("Tile");
		else if(i == 1)
			typeButtons[i]->SetTextString("Obstacles");
		else if(i == 2)
			typeButtons[i]->SetTextString("Enemies");
		typeButtons[i]->SetTextColor(sf::Color::White);
		typeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
	}

	LoadBackGround("graphics/basement/basement.csv");
}

void EditBoxUI::Update(float dt)
{
	for (int i = 0; i < 3; i++)
	{
		typeButtons[i]->Update(dt);
	}
}

void EditBoxUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	for (int i = 0; i < 3; i++)
	{
		typeButtons[i]->Draw(window);
	}
	for (int i = 0; i < basementGround.size(); i++)
	{
		window.draw(basementGround[i]);
	}
}

void EditBoxUI::LoadBackGround(const std::string& filePath )
{
	rapidcsv::Document doc(filePath);

	int count = doc.GetRowCount();

	for (int i = 0; i < count; i++)
	{
		auto row = doc.GetRow<std::string>(i);
		basementGround.push_back(sf::Sprite());
		basementGround[i].setTexture(TEXTURE_MGR.Get(basementGroundId));
		basementGround[i].setTextureRect({std::stoi(row[0]), std::stoi(row[1]) ,std::stoi(row[2]) ,std::stoi(row[3]) });
		basementGround[i].setOrigin(sf::Vector2f(std::stoi(row[2]) ,std::stoi(row[3])) * 0.5f);
		basementGround[i].setPosition(position + sf::Vector2f((i % 5 - 2) * (std::stof(row[2]) * 2.f),(i / 5 - (count / 5)) * std::stof(row[3]) * 2.f));
		basementGround[i].setScale({ gridSize.x / std::stof(row[2]), gridSize.y / std::stof(row[3]) });
	}
}
