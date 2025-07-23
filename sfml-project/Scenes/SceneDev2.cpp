#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "Isaac.h"
#include "Tears.h"
#include "Monster.h"
#include "SpriteGo.h"
#include "Fly.h"
#include "Spider.h"

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
	background->SetPosition({ -500.f, -500.f });
	AddGameObject(background);

	AddGameObject(new Isaac());

	auto fly = new Fly();
	fly->SetPosition({ 0.f,0.f });
	AddGameObject(fly);

	auto spider = new Spider();
	spider->SetPosition({ 0.f, 0.f });
	AddGameObject(spider);

	Scene::Init();
}

void SceneDev2::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center { size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, -200.f });

	Scene::Enter();
}

void SceneDev2::Update(float dt)
{
	Isaac* isaac = nullptr;
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
}