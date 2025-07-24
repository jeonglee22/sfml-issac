#include "stdafx.h"
#include "SceneGame.h"
#include "rapidcsv.h"
#include "SpriteGo.h"
#include "Isaac.h"
#include "Tears.h"
#include "Monster.h"
#include "Fly.h"
#include "Spider.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Stage)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/background/basement.png");
	texIds.push_back("graphics/background/sheol.png");
	texIds.push_back("graphics/background/caves.png");
	texIds.push_back("graphics/background/depths.png");
	texIds.push_back("graphics/obstacles/grid_spikes.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_basement.png");
	texIds.push_back("graphics/character_001_isaac.png");
	texIds.push_back("graphics/only_tears.png");
	texIds.push_back("graphics/monster_010_fly.png");
	texIds.push_back("graphics/temp_background.png");
	texIds.push_back("graphics/monster_214_level2spider_small.png");
	texIds.push_back("graphics/effects/effect_015_tearpoofa.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");

	ANI_CLIP_MGR.Load("animations/empty.csv");

	ANI_CLIP_MGR.Load("animations/isaac_body_idle.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_front.csv");
	ANI_CLIP_MGR.Load("animations/isaac_run_height.csv");
	ANI_CLIP_MGR.Load("animations/isaac_run_weight.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_side.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_rare.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_front_tears.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_side_tears.csv");
	ANI_CLIP_MGR.Load("animations/isaac_head_rare_tears.csv");
	ANI_CLIP_MGR.Load("animations/isaac_hurt.csv");


	ANI_CLIP_MGR.Load("animations/fly.csv");
	ANI_CLIP_MGR.Load("animations/spider_patrol.csv");
	ANI_CLIP_MGR.Load("animations/spider_charge.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");

	ANI_CLIP_MGR.Load("animations/tears_idle.csv");
	ANI_CLIP_MGR.Load("animations/tears_boom.csv");

	AddGameObject(new Isaac());


	auto fly = new Fly();
	fly->SetPosition({ 200.f,200.f });
	AddGameObject(fly);

	auto fly1 = new Fly();
	fly1->SetPosition({ 250.f,250.f });
	AddGameObject(fly1);

	auto spider = new Spider();
	spider->SetPosition({ 300.f, 300.f });
	AddGameObject(spider);

	auto spider1 = new Spider();
	spider1->SetPosition({ 350.f, 350.f });
	AddGameObject(spider1);



	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();

	LoadStageField("Mapfolder/testmap.csv");
}

void SceneGame::Update(float dt)
{
	for (auto& gameObject : gameObjects)
	{
		if (auto player = dynamic_cast<Isaac*>(gameObject))
		{
			isaac = player;
		}
		if (auto monster = dynamic_cast<Monster*>(gameObject))
		{
			monsters.push_back(monster);
		}
	}

	if (isaac)
	{
		sf::Vector2f playerPos = isaac->GetPosition();
		for (auto& monster : monsters)
		{
			monster->SetPlayerPosition(playerPos);
		}
	}

	Scene::Update(dt);
}

void SceneGame::LoadStageField(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	mapSprites.clear();
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		std::vector<std::string> infos = doc.GetRow<std::string>(i);
		mapSprites.push_back(new SpriteGo(infos[0], infos[5]));
		mapSprites[i]->Init();
		mapSprites[i]->SetOrigin(Origins::MC);
		mapSprites[i]->Reset();
		mapSprites[i]->GetSprite().setTextureRect({std::stoi(infos[2]),std::stoi(infos[1]), std::stoi(infos[3]), std::stoi(infos[4]) });
		mapSprites[i]->SetScale({ 60.f / std::stof(infos[3]) , 60.f / std::stof(infos[4]) });
		mapSprites[i]->SetOrigin(Origins::MC);
		mapSprites[i]->SetPosition({ std::stof(infos[6]), std::stof(infos[7]) });
		mapSprites[i]->SetRotation(std::stof(infos[12]));
		mapSprites[i]->sortingLayer = (SortingLayers) std::stoi(infos[10]);
		mapSprites[i]->sortingOrder = std::stoi(infos[11]);
		AddGameObject(mapSprites[i]);
	}
}

void SceneGame::EnemyCollosion()
{
	for (auto& gameObject : gameObjects)
	{
		if (auto player = dynamic_cast<Isaac*>(gameObject))
		{
			isaac = player;
		}
		if (auto monster = dynamic_cast<Monster*>(gameObject))
		{
			monsters.push_back(monster);
		}
	}

	if (isaac)
	{
		sf::Vector2f playerPos = isaac->GetPosition();
		for (auto& monster : monsters)
		{
			monster->SetPlayerPosition(playerPos);
		}
	}


}
