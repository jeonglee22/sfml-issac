#include "stdafx.h"
#include "EditBoxUI.h"
#include "rapidcsv.h"
#include "SpriteGo.h"

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

	pickBox.setSize({60.f,60.f});
	pickBox.setOutlineColor(sf::Color::Red);
	pickBox.setFillColor(sf::Color::Transparent);
	pickBox.setOutlineThickness(3.f);
	pickBox.setOrigin({ 30.f,30.f });

	basementGroundId = "graphics/background/01_basement.png";
	cavesGroundId = "graphics/background/03_caves.png";
	depthsGroundId = "graphics/background/05_depths.png";
	sheolGroundId = "graphics/background/09_sheol.png";

	for(int i = 0; i < 3; i++)
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

	InitStyleTypeButtons();
	InitObstacleTypeButtons();
	InitEnemyTypeButtons();
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
		auto buttonFunc = [this, i]() {
			auto buttons = i == 0 ? styleTypeButtons : (i==1 ? obstacleTypeButtons : enemyTypeButtons) ;
			DisableAllButtons();
			for (auto button : buttons)
			{
				button->SetActive(true);
			}
		};
		typeButtons[i]->SetButtonFunc(buttonFunc);
	}

	ResetStyleTypeButtons();
	ResetEnemyTypeButtons();
	ResetObstacleTypeButtons(-450.f);

	LoadBackGround("graphics/background/basement.csv");

	pickBox.setPosition(position + sf::Vector2f(0.f, 500.f));
}

void EditBoxUI::Update(float dt)
{
	for (int i = 0; i < 3; i++)
	{
		typeButtons[i]->Update(dt);
		enemyTypeButtons[i]->Update(dt);
	}
	for (int i = 0; i < 4; i++)
	{
		styleTypeButtons[i]->Update(dt);
		obstacleTypeButtons[i]->Update(dt);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R) && pickedSprite != nullptr)
	{
		pickedSprite->SetRotation(pickedSprite->GetRotation() + 90.f);
	}
}

void EditBoxUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	for (int i = 0; i < 3; i++)
	{
		typeButtons[i]->Draw(window);
		if (enemyTypeButtons[i]->GetActive())
			enemyTypeButtons[i]->Draw(window);
	}
	for (int i = 0; i < 4; i++)
	{
		if(styleTypeButtons[i]->GetActive())
			styleTypeButtons[i]->Draw(window);
		if(obstacleTypeButtons[i]->GetActive())
			obstacleTypeButtons[i]->Draw(window);
	}
	for (int i = 0; i < basementGround.size(); i++)
	{
		basementGround[i]->Draw(window);
	}
	window.draw(pickBox);
	if(isPicked)
	{
		pickedSprite->Draw(window);
	}
}

void EditBoxUI::InitStyleTypeButtons()
{
	for (int i = 0; i < 4; i++)
	{
		styleTypeButtons.push_back(new Button());
		styleTypeButtons[i]->Init();
		styleTypeButtons[i]->SetButtonRectSize({ 120.f, 30.f });
		styleTypeButtons[i]->SetButtonRectColor(sf::Color::Black);
		styleTypeButtons[i]->SetButtonRectOrigin({ 60.f, 15.f });
		styleTypeButtons[i]->SetButtonRectOutlineColor(sf::Color::Black);
		styleTypeButtons[i]->SetButtonRectOutlineThickness(3.f);
		styleTypeButtons[i]->SetTextSize(25);
		styleTypeButtons[i]->SetActive(false);
	}
}

void EditBoxUI::InitObstacleTypeButtons()
{
	for (int i = 0; i < 4; i++)
	{
		obstacleTypeButtons.push_back(new Button());
		obstacleTypeButtons[i]->Init();
		obstacleTypeButtons[i]->SetButtonRectSize({ 120.f, 30.f });
		obstacleTypeButtons[i]->SetButtonRectColor(sf::Color::Black);
		obstacleTypeButtons[i]->SetButtonRectOrigin({ 60.f, 15.f });
		obstacleTypeButtons[i]->SetButtonRectOutlineColor(sf::Color::Black);
		obstacleTypeButtons[i]->SetButtonRectOutlineThickness(3.f);
		obstacleTypeButtons[i]->SetTextSize(25);
		obstacleTypeButtons[i]->SetActive(false);
	}
}

void EditBoxUI::InitEnemyTypeButtons()
{
	for (int i = 0; i < 3; i++)
	{
		enemyTypeButtons.push_back(new Button());
		enemyTypeButtons[i]->Init();
		enemyTypeButtons[i]->SetButtonRectSize({ 120.f, 30.f });
		enemyTypeButtons[i]->SetButtonRectColor(sf::Color::Black);
		enemyTypeButtons[i]->SetButtonRectOrigin({ 60.f, 15.f });
		enemyTypeButtons[i]->SetButtonRectOutlineColor(sf::Color::Black);
		enemyTypeButtons[i]->SetButtonRectOutlineThickness(3.f);
		enemyTypeButtons[i]->SetTextSize(25);
		enemyTypeButtons[i]->SetActive(false);
	}
}

void EditBoxUI::ResetStyleTypeButtons()
{
	for (int i = 0; i < 4; i++)
	{
		styleTypeButtons[i]->Reset();
		styleTypeButtons[i]->SetPosition(position + sf::Vector2f(-225.f + i * 150.f, -450.f));
		styleTypeButtons[i]->SetTextPosition({ 0.f, -10.f });
		if (i == 0)
			styleTypeButtons[i]->SetTextString("Basement");
		else if (i == 1)
			styleTypeButtons[i]->SetTextString("sheol");
		else if (i == 2)
			styleTypeButtons[i]->SetTextString("depth");
		else if (i == 3)
			styleTypeButtons[i]->SetTextString("cave");
		styleTypeButtons[i]->SetTextColor(sf::Color::White);
		styleTypeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
	}
}

void EditBoxUI::ResetObstacleTypeButtons(float yPos)
{
	for (int i = 0; i < 4; i++)
	{
		obstacleTypeButtons[i]->Reset();
		obstacleTypeButtons[i]->SetPosition(position + sf::Vector2f(-225.f + i * 150.f, yPos));
		obstacleTypeButtons[i]->SetTextPosition({ 0.f, -10.f });
		if (i == 0)
			obstacleTypeButtons[i]->SetTextString("Rocks");
		else if (i == 1)
			obstacleTypeButtons[i]->SetTextString("CampFile");
		else if (i == 2)
			obstacleTypeButtons[i]->SetTextString("Spike");
		else if (i == 3)
			obstacleTypeButtons[i]->SetTextString("Pit");
		obstacleTypeButtons[i]->SetTextColor(sf::Color::White);
		obstacleTypeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
	}
}

void EditBoxUI::ResetEnemyTypeButtons()
{
	for (int i = 0; i < 3; i++)
	{
		enemyTypeButtons[i]->Reset();
		enemyTypeButtons[i]->SetPosition(position + sf::Vector2f(-150.f + i * 150.f, -450.f));
		enemyTypeButtons[i]->SetTextPosition({ 0.f, -10.f });
		if (i == 0)
			enemyTypeButtons[i]->SetTextString("Ground");
		else if (i == 1)
			enemyTypeButtons[i]->SetTextString("Flight");
		else if (i == 2)
			enemyTypeButtons[i]->SetTextString("Boss");
		enemyTypeButtons[i]->SetTextColor(sf::Color::White);
		enemyTypeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
	}
}

void EditBoxUI::LoadBackGround(const std::string& filePath )
{
	rapidcsv::Document doc(filePath);

	int count = doc.GetRowCount();

	for (int i = 0; i < count; i++)
	{
		auto row = doc.GetRow<std::string>(i);
		basementGround.push_back(new SpriteGo());
		basementGround[i]->GetSprite().setTexture(TEXTURE_MGR.Get(basementGroundId));
		basementGround[i]->GetSprite().setTextureRect({std::stoi(row[0]), std::stoi(row[1]) ,std::stoi(row[2]) ,std::stoi(row[3]) });
		basementGround[i]->SetOrigin(sf::Vector2f(std::stoi(row[2]) ,std::stoi(row[3])) * 0.5f);
		basementGround[i]->SetPosition(position + sf::Vector2f((i % 5 - 2) * (std::stof(row[2]) * 2.f),(i / 5 - (count / 5)) * std::stof(row[3]) * 2.f));
		basementGround[i]->SetScale({ gridSize.x / std::stof(row[2]), gridSize.y / std::stof(row[3]) });
	}
}

SpriteGo* EditBoxUI::SetChoosedSprite(SpriteGo* sp)
{
	isPicked = true;
	pickedSprite = new SpriteGo(*sp);
	pickedSprite->SetPosition(pickBox.getPosition());
	return pickedSprite;
}

void EditBoxUI::SetOffChoosedSprite()
{
	isPicked = false;
	if (pickedSprite != nullptr)
		delete pickedSprite;
	pickedSprite = nullptr;
}

void EditBoxUI::DisableAllButtons()
{
	for (int i = 0; i < 3; i++)
	{
		enemyTypeButtons[i]->SetActive(false);
	}
	for (int i = 0; i < 4; i++)
	{
		styleTypeButtons[i]->SetActive(false);
		obstacleTypeButtons[i]->SetActive(false);
	}
}
