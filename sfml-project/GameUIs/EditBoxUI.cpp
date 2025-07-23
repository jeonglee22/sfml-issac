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

	for (int i = 0; i < 3; i++)
	{
		filenames.push_back("");
	}

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

	std::string typeNames[3] = { "background", "obstacles", "enemies" };
	for (int i = 0; i < 3; i++)
	{
		typeButtons[i]->Reset();
		typeButtons[i]->SetPosition(position + sf::Vector2f(-150.f + i * 150.f, -500.f));
		typeButtons[i]->SetTextPosition({ 0.f, -10.f });
		typeButtons[i]->SetTextString(typeNames[i]);
		typeButtons[i]->SetTextColor(sf::Color::White);
		typeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
		auto buttonFunc = [this, i, typeNames]() {
			auto buttons = i == 0 ? styleTypeButtons : (i==1 ? obstacleTypeButtons : enemyTypeButtons);
			std::fill(filenames.begin(), filenames.end(), "");
			filenames[0] = typeNames[i];
			DisableAllButtons();
			if (i == 0)
				ResetStyleTypeButtons();
			for (auto button : buttons)
			{
				button->SetActive(true);
			}
		};
		typeButtons[i]->SetButtonFunc(buttonFunc);
	}

	ResetStyleTypeButtons();
	ResetEnemyTypeButtons();
	ResetObstacleTypeButtons();

	pickBox.setPosition(position + sf::Vector2f(0.f, 400.f));

	isFinishFilename = false;
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
	if (InputMgr::GetKeyDown(sf::Keyboard::Q) && pickedSprite != nullptr)
	{
		pickedSprite->SetScale({pickedSprite->GetScale().x * -1.f,pickedSprite->GetScale().y});
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::E) && pickedSprite != nullptr)
	{
		pickedSprite->SetScale({ pickedSprite->GetScale().x,pickedSprite->GetScale().y * -1.f });
	}

	if(isFinishFilename)
	{
		isFinishFilename = false;
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
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->Draw(window);
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

void EditBoxUI::ResetStyleTypeButtons(float yPos)
{
	std::string names[4] = { "basement", "depth", "sheol", "cave" };
	for (int i = 0; i < 4; i++)
	{
		std::string name = names[i];
		styleTypeButtons[i]->Reset();
		styleTypeButtons[i]->SetPosition(position + sf::Vector2f(-225.f + i * 150.f, yPos));
		styleTypeButtons[i]->SetTextPosition({ 0.f, -10.f });
		styleTypeButtons[i]->SetTextString(name);
		styleTypeButtons[i]->SetTextColor(sf::Color::White);
		styleTypeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
		auto styleFunc = [this, name, yPos]() {
			if (yPos == -400.f)
			{
				filenames[2] = name;
			}
			else
			{
				filenames[1] = name;
			}
			LoadTextureFile(filenames);
			isFinishFilename = true;
		};
		styleTypeButtons[i]->SetButtonFunc(styleFunc);
	}
}

void EditBoxUI::ResetObstacleTypeButtons()
{
	std::string names[4] = {"rocks", "fire", "spike", "pit"};
	for (int i = 0; i < 4; i++)
	{
		std::string name = names[i];
		obstacleTypeButtons[i]->Reset();
		obstacleTypeButtons[i]->SetPosition(position + sf::Vector2f(-225.f + i * 150.f, -450.f));
		obstacleTypeButtons[i]->SetTextPosition({ 0.f, -10.f });
		obstacleTypeButtons[i]->SetTextString(name);
		obstacleTypeButtons[i]->SetTextColor(sf::Color::White);
		obstacleTypeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
		auto buttonFunc = [this, name]() {
			if (name == "rocks" || name == "pit")
			{
				filenames[1] = name;
				ResetStyleTypeButtons(-400.f);
				for (int i = 0; i < styleTypeButtons.size(); i++)
				{
					if(i > 1)
					{
						if (name != "pit")
							styleTypeButtons[i]->SetActive(true);
					}
					else
					{
						styleTypeButtons[i]->SetActive(true);
					}
				}
			}
			else
			{
				for (auto button : styleTypeButtons)
				{
					button->SetActive(false);
				}
				filenames[1] = name;
				filenames[2] = "";
				LoadTextureFile(filenames);
				isFinishFilename = true;
			}
		};
		obstacleTypeButtons[i]->SetButtonFunc(buttonFunc);
	}
}

void EditBoxUI::ResetEnemyTypeButtons()
{
	std::string names[3] = { "ground", "flight", "boss" };
	for (int i = 0; i < 3; i++)
	{
		std::string name = names[i];
		enemyTypeButtons[i]->Reset();
		enemyTypeButtons[i]->SetPosition(position + sf::Vector2f(-150.f + i * 150.f, -450.f));
		enemyTypeButtons[i]->SetTextPosition({ 0.f, -10.f });
		enemyTypeButtons[i]->SetTextString(name);
		enemyTypeButtons[i]->SetTextColor(sf::Color::White);
		enemyTypeButtons[i]->SetButtonRectPosition({ 0.f,0.f });
		auto enemyFunc = [this, name]() {
			filenames[1] = name;
			filenames[2] = "";
			LoadTextureFile(filenames);
			isFinishFilename = true;
		};
		enemyTypeButtons[i]->SetButtonFunc(enemyFunc);
	}
}

void EditBoxUI::LoadTextureFile(const std::vector<std::string>& filenames )
{
	std::string filePath = "graphics";
	for (auto name : filenames)
	{
		if (name != "")
		{
			filePath += "/" + name;
		}
	}
	filePath += ".csv";
	rapidcsv::Document doc(filePath);
	textures.clear();

	int count = doc.GetRowCount();

	for (int i = 0; i < count; i++)
	{
		auto row = doc.GetRow<std::string>(i);
		std::string name;
		int pos = row[0].find_last_of("/");
		int pos2 = row[0].find_last_of(".");
		name = row[0].substr(pos + 1, pos2 - pos - 1);
		textures.push_back(new SpriteGo(row[0], name));
		if (filenames[0] == "background")
		{
			textures[i]->sortingLayer = SortingLayers::Background;
			textures[i]->sortingOrder = 0;
		}
		else
		{
			textures[i]->sortingLayer = SortingLayers::Foreground;
			textures[i]->sortingOrder = -5;
		}
		textures[i]->GetSprite().setTexture(TEXTURE_MGR.Get(row[0]));
		textures[i]->GetSprite().setTextureRect({std::stoi(row[1]), std::stoi(row[2]) ,std::stoi(row[3]) ,std::stoi(row[4]) });
		textures[i]->SetOrigin(sf::Vector2f(std::stoi(row[3]) ,std::stoi(row[4])) * 0.5f);
		textures[i]->SetPosition(position + sf::Vector2f((i % 5 - 2) * 60.f * 1.5f,(i / 5 - 4.5f) * 60.f * 1.5f) + sf::Vector2f(0,100.f));
		textures[i]->SetScale({ gridSize.x / std::stof(row[3]), gridSize.y / std::stof(row[4]) });
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
