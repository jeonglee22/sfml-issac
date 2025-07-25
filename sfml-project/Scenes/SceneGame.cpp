#include "stdafx.h"
#include "SceneGame.h"
#include "rapidcsv.h"
#include "SpriteGo.h"
#include "Isaac.h"
#include "Tears.h"
#include "Monster.h"
#include "Fly.h"
#include "Spider.h"
#include "Obstacles.h"
#include "Walls.h"
#include "Spikes.h"
#include "HitBox.h"
#include "Door.h"

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
	texIds.push_back("graphics/effects/effect_015_tearpoofa.png");
	texIds.push_back("graphics/additionals/door_01_normaldoor.png");
	texIds.push_back("graphics/shading.png");

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
	ANI_CLIP_MGR.Load("animations/isaac_dead.csv");


	ANI_CLIP_MGR.Load("animations/fly.csv");
	ANI_CLIP_MGR.Load("animations/spider_patrol.csv");
	ANI_CLIP_MGR.Load("animations/spider_charge.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");

	ANI_CLIP_MGR.Load("animations/tears_idle.csv");
	ANI_CLIP_MGR.Load("animations/tears_boom.csv");

	isaac = (Isaac*)AddGameObject(new Isaac());

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

	for (int i = 0; i < 4; i++)
	{
		doors.push_back((Door*)AddGameObject(new Door("graphics/additionals/door_01_normaldoor.png", "Door")));
	}

	shading = (SpriteGo*)AddGameObject(new SpriteGo("graphics/shading.png"));
	shading->sortingLayer = SortingLayers::Background;
	shading->sortingOrder = 20;

	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setSize({ 960, 540 });
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);

	Scene::Enter();

	isaac->SetPosition(center - sf::Vector2f(0,100.f));

	LoadStageField("Mapfolder/testmap3.csv");
	mapOffset = sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f;

	MakeBoundary();

	MakeDoor();

	shading->SetScale({ 2.f,2.f });
	shading->SetOrigin(sf::Vector2f(TEXTURE_MGR.Get("graphics/shading.png").getSize()) * 0.5f);
	shading->SetPosition(currentMapSize.getSize() * 0.5f);
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

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	for (int i = 0; i < boundary.size(); i++)
		boundary[i]->Draw(window);
}

void SceneGame::LoadStageField(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	currentMapSize = sf::FloatRect(doc.GetCell<float>(0, 0), doc.GetCell<float>(1, 0), doc.GetCell<float>(2, 0), doc.GetCell<float>(3, 0) );
	worldView.setSize(currentMapSize.getSize());
	worldView.setCenter(currentMapSize.getSize()*0.5f);

	mapSprites.clear();
	for (int i = 0; i < doc.GetRowCount()-1; i++)
	{
		std::vector<std::string> infos = doc.GetRow<std::string>(i+1);
		CreateMatchedTypeGO(infos[0], infos[5]);
		mapSprites[i]->Init();
		mapSprites[i]->SetOrigin(Origins::MC);
		mapSprites[i]->Reset();
		mapSprites[i]->GetSprite().setTextureRect({std::stoi(infos[2]),std::stoi(infos[1]), std::stoi(infos[3]), std::stoi(infos[4]) });
		mapSprites[i]->SetScale({ 2.f,2.f });
		mapSprites[i]->SetOrigin({ std::stof(infos[13]) ,std::stof(infos[14]) });
		mapSprites[i]->SetPosition(sf::Vector2f( std::stof(infos[6]), std::stof(infos[7]) ) + sf::Vector2f(currentMapSize.left,currentMapSize.top) * -1.f);
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

void SceneGame::MakeBoundary()
{
	std::vector<HitBox*> hitBoxes;
	float left = currentMapSize.left, top = currentMapSize.top, width = currentMapSize.width, height = currentMapSize.height;

	for (int i = 0; i < 4; i++)
	{
		boundary.push_back(new HitBox());
		boundary.push_back(new HitBox());
		if (i < 2)
		{
			//boundary[i]->rect.setSize({ currentMapSize.width, 104.f });
			sf::Vector2f rowBound = { (currentMapSize.width - doors[0]->GetDoorSize().x) * 0.5f, 104.f };
			boundary[i * 2]->rect.setSize(rowBound);
			boundary[i * 2 + 1]->rect.setSize(rowBound);
			boundary[i * 2]->rect.setOrigin({rowBound.x + doors[0]->GetDoorSize().x * 0.5f, 52.f});
			boundary[i * 2 + 1]->rect.setOrigin({ -doors[0]->GetDoorSize().x * 0.5f, 52.f });
		}
		else
		{
			//boundary[i]->rect.setSize({ 104.f, currentMapSize.height });
			sf::Vector2f colBound = { 104.f, (currentMapSize.height - doors[0]->GetDoorSize().x) * 0.5f };
			boundary[i * 2]->rect.setSize(colBound);
			boundary[i * 2 + 1]->rect.setSize(colBound);
			boundary[i * 2]->rect.setOrigin({52.f, colBound.y + doors[0]->GetDoorSize().x * 0.5f });
			boundary[i * 2 + 1]->rect.setOrigin({52.f, -doors[0]->GetDoorSize().x * 0.5f });
		}
	}
	boundary[0]->rect.setPosition({ currentMapSize.getSize().x * 0.5f, 52.f });
	boundary[1]->rect.setPosition({ currentMapSize.getSize().x * 0.5f, 52.f });
	boundary[2]->rect.setPosition({ currentMapSize.getSize().x * 0.5f, currentMapSize.getSize().y - 52.f });
	boundary[3]->rect.setPosition({ currentMapSize.getSize().x * 0.5f, currentMapSize.getSize().y - 52.f });
	boundary[4]->rect.setPosition({ 52.f, currentMapSize.getSize().y * 0.5f });
	boundary[5]->rect.setPosition({ 52.f, currentMapSize.getSize().y * 0.5f });
	boundary[6]->rect.setPosition({ currentMapSize.getSize().x - 52.f, currentMapSize.getSize().y * 0.5f });
	boundary[7]->rect.setPosition({ currentMapSize.getSize().x - 52.f, currentMapSize.getSize().y * 0.5f });
}

void SceneGame::MakeDoor()
{
	float width = currentMapSize.width, height = currentMapSize.height;
	for (int i = 0; i < 4; i++)
	{
		// 0 1 2 3
		sf::Vector2f localPos;
		localPos.x = (width * 0.5f - boundary[0]->rect.getSize().y) * (i % 2 == 1 ? 2.f - i : 0.f);
		localPos.y = (height * 0.5f - boundary[0]->rect.getSize().y) * (i % 2 == 0 ? i - 1.f : 0.f);
		doors[i]->SetPosition(currentMapSize.getSize() * 0.5f + localPos);
		doors[i]->SetRotation(90.f * i);
	}
}

void SceneGame::CreateMatchedTypeGO(const std::string& filepath, const std::string& name)
{
	if (name == "rocks_basement" || name == "grid_pit_basement")
	{
		mapSprites.push_back(new Obstacles(filepath, name));
	}
	else if (name == "grid_spikes")
	{
		mapSprites.push_back(new Spikes(filepath, name));
	}
	else
	{
		mapSprites.push_back(new SpriteGo(filepath, name));
	}
}
