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
	texIds.push_back("graphics/obstacles/grid_fireplace.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_basement.png");
	texIds.push_back("graphics/obstacles/pit/grid_pit_basement.png");
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

	AddGameObject(new Isaac());


	auto fly = new Fly();
	fly->SetPosition({ 200.f,200.f });
	AddGameObject(fly);

	auto spider = new Spider();
	spider->SetPosition({ 300.f, 300.f });
	AddGameObject(spider);



	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setSize({ 960, 540 });
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);

	size = sf::Vector2f(960.f, 570.f);
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	Scene::Enter();

	LoadStageField("Mapfolder/testmap3.csv");
}

void SceneGame::Update(float dt)
{
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
		mapSprites[i]->SetScale({ 2.f,2.f });
		mapSprites[i]->SetOrigin({ std::stof(infos[13]) ,std::stof(infos[14]) });
		mapSprites[i]->SetPosition(sf::Vector2f( std::stof(infos[6]), std::stof(infos[7]) ) + sf::Vector2f(140.f, 104.f));
		mapSprites[i]->SetRotation(std::stof(infos[12]));
		mapSprites[i]->sortingLayer = (SortingLayers) std::stoi(infos[10]);
		mapSprites[i]->sortingOrder = std::stoi(infos[11]);
		AddGameObject(mapSprites[i]);
	}
}
