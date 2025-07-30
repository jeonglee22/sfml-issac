#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "Isaac.h"
#include "Tears.h"
#include "Monster.h"
#include "SpriteGo.h"
#include "Fly.h"
#include "Spider.h"
#include "SkillBible.h"
#include "Skill.h"
#include "HitBox.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	texIds.push_back("graphics/character_001_isaac.png");
	texIds.push_back("graphics/only_tears.png");
	texIds.push_back("graphics/monster_010_fly.png");
	texIds.push_back("graphics/temp_background.png");
	texIds.push_back("graphics/monster_214_level2spider_small.png");
	texIds.push_back("graphics/additionals/levelitem_001_itemaltar.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/isaac_body_idle.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_front.csv");
	ANI_CLIP_MGR.Load("animations/isaac_run_height.csv");
	ANI_CLIP_MGR.Load("animations/isaac_run_weight.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_side.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_rare.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_front_tears.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_side_tears.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_rare_tears.csv");
	ANI_CLIP_MGR.Load("animations/fly.csv");
	ANI_CLIP_MGR.Load("animations/spider_patrol.csv");
	ANI_CLIP_MGR.Load("animations/spider_charge.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");

	SpriteGo* background = new SpriteGo("graphics/temp_background.png");
	background->sortingLayer = SortingLayers::Background;
	background->SetOrigin(Origins::MC);
	background->SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	AddGameObject(background);

	alter = new SpriteGo("graphics/additionals/levelitem_001_itemaltar.png");
	alter->sortingLayer = SortingLayers::Foreground;
	alter->sortingOrder = 0;
	AddGameObject(alter);

	isaac = (Isaac*)AddGameObject(new Isaac());
	isaac->sortingLayer = SortingLayers::Foreground;
	isaac->sortingOrder = 2;

	hitBox = new HitBox();

	auto fly = new Fly();
	fly->SetPosition({ 0.f,0.f });
	AddGameObject(fly);

	auto spider = new Spider();
	spider->SetPosition({ 0.f, 0.f });
	AddGameObject(spider);

	Scene::Init();

	skillBible = new SkillBible();
	skillBible->LoadJsonFile("graphics/items/items.json");
}

void SceneDev2::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center { size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();

	alter->GetSprite().setTextureRect({ 0,0,32,32 });
	alter->SetOrigin(Origins::MC);
	alter->SetScale({ 2.f,2.f });
	alter->SetPosition(worldView.getCenter());

	isaac->SetPosition(alter->GetPosition() + sf::Vector2f(0, 150.f));
}

void SceneDev2::Update(float dt)
{
	std::vector<Monster*> monsters;

	for (auto& gameObject : gameObjects) {
		if (auto player = dynamic_cast<Isaac*>(gameObject)) {
			isaac = player;
		}
		if (auto monster = dynamic_cast<Monster*>(gameObject)) {
			monsters.push_back(monster);
		}
	}

	if (isaac) {
		sf::Vector2f playerPos = isaac->GetPosition();
		for (auto& monster : monsters) {
			monster->SetPlayerPosition(playerPos);
		}
	}


	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Q))
	{
		if (skill != nullptr)
		{
			RemoveGameObject(skill);
			skill = nullptr;
		}

		skillBible->PickJsonRandomInfo();
		skillBible->PickSkill();
		skill = skillBible->GetSkill();

		skill->sortingLayer = SortingLayers::Foreground;
		skill->sortingOrder = 1;
		skill->Reset();
		skill->SetPosition(alter->GetPosition() + sf::Vector2f(0, -40.f));
		skill->SetScale({2.f,2.f});

		AddGameObject(skill);
	}

	if (skill != nullptr)
	{
		skill->SetPosition(skill->GetPosition() + sf::Vector2f(0, dir) * dt * 5.f);
		movingTime += dt;
		if (movingTime > movingTimeMax)
		{
			dir *= -1.f;
			movingTime = 0.f;
		}
	}

	hitBox->UpdateTransform(alter->GetSprite(), alter->GetSprite().getLocalBounds());
	hitBox->rect.setScale(hitBox->rect.getScale() * 0.5f);

	if (Utils::CheckCollision(hitBox->rect, isaac->GetHitBoxBody().rect))
	{
		isaac->SetSkill(skill);
		std::cout << "Get Item!!!" << std::endl;
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	hitBox->Draw(window);
}

