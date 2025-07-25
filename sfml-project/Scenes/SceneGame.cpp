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
#include "Map.h"

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
	texIds.push_back("graphics/overlay_2.png");

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

	maps.push_back((Map*)AddGameObject(new Map("Mapfolder/startMap.csv")));
	maps.push_back((Map*)AddGameObject(new Map("Mapfolder/testmap3.csv")));

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

	currentMapSize = maps[0]->GetMapSize();
	worldView.setSize(currentMapSize.getSize());
	worldView.setCenter(currentMapSize.getSize() * 0.5f);
	isaac->SetPosition(center);

	//LoadStageField("Mapfolder/testmap3.csv");
	mapOffset = sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f;

	for (int i = 0; i < maps.size(); i++)
	{
		maps[i]->SetDoor();
		maps[i]->SetBoundary();
		maps[i]->AddGameObjectInScene();
		if (i == 1)
		{
			maps[1]->AddFly({ 200.f,200.f });
			maps[1]->AddFly({ 250.f,250.f });
			maps[1]->AddSpider({ 300.f, 300.f });
			maps[1]->AddSpider({ 350.f, 350.f });
		}
		if (i > 0)
			maps[i]->SetPosition(maps[i]->GetPosition() + sf::Vector2f(maps[i - 1]->GetMapSize().getSize().x, 0.f));
	}

	maps[0]->SetMapPlaying(1);

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

void SceneGame::GoNextMap()
{
	Map* currentMap = maps[currentMapIndex];
	for (auto door : currentMap->GetDoor())
	{
		//if(Utils::CheckCollision(hitBoxBody.rect, currentMap->GetDoor()->GetHitBox()->rect))
	}
}

