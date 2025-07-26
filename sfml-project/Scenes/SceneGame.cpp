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
#include "MapUI.h"
#include "ItemUI.h"
#include "HeartUI.h"

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
	texIds.push_back("graphics/additionals/door_01_normaldoor.png");
	texIds.push_back("graphics/shading.png");
	texIds.push_back("graphics/overlay_2.png");
	texIds.push_back("graphics/effect_002_bloodpoof_large1.png");
	texIds.push_back("graphics/effect_002_bloodpoof.png");
	texIds.push_back("graphics/minimap.png");
	texIds.push_back("graphics/hudpickups.png");
	texIds.push_back("graphics/ui_hearts.png");
	for (int i = 0; i < 10; i++)
		texIds.push_back("fonts/fontimage/" + std::to_string(i) + ".png");

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
	ANI_CLIP_MGR.Load("animations/fly_dead.csv");
	ANI_CLIP_MGR.Load("animations/spider_patrol.csv");
	ANI_CLIP_MGR.Load("animations/spider_charge.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");
	ANI_CLIP_MGR.Load("animations/blood.csv");
	ANI_CLIP_MGR.Load("animations/blood_small.csv");

	ANI_CLIP_MGR.Load("animations/tears_idle.csv");
	ANI_CLIP_MGR.Load("animations/tears_boom.csv");

	isaac = (Isaac *)AddGameObject(new Isaac());

	maps.push_back((Map *)AddGameObject(new Map("Mapfolder/startMap.csv")));
	maps[0]->SetStageIndex(7, 7);
	maps.push_back((Map *)AddGameObject(new Map("Mapfolder/testmap3.csv")));
	maps[1]->SetStageIndex(8, 7);
	maps.push_back((Map *)AddGameObject(new Map("Mapfolder/testmap3.csv")));
	maps[2]->SetStageIndex(9, 7);

	for(int i =0; i <1;i++)
	{
		shadings.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/shading.png")));

		shadings[i]->sortingLayer = SortingLayers::Background;
		shadings[i]->sortingOrder = 20;
	}

	mapUI = (MapUI*)AddGameObject(new MapUI("graphics/minimap.png", "mapUI"));
	itemUI = (ItemUI*)AddGameObject(new ItemUI("ItemUI"));
	heartUI = (HeartUI*)AddGameObject(new HeartUI("graphics/ui_hearts.png", "HeartUI"));

	Scene::Init();
}

void SceneGame::Enter()
{
	for (int i = 0 ; i< 15; i++)
	{
		for (int j = 0; j < 15; j++)
			mapIndex[i][j] = -1;
	}

	FRAMEWORK.GetWindow().setSize({960, 540});
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{size.x * 0.5f, size.y * 0.5f};
	uiView.setSize(size);
	uiView.setCenter(center);

	Scene::Enter();

	mapUI->SetScale({ 2.f,2.f });
	itemUI->SetScale({ 2.f,2.f });
	heartUI->SetScale({ 2.f,2.f });

	mapIndex[stageStartY][stageStartX] = 0;
	mapIndex[stageStartY][stageStartX + 1] = 1;
	mapIndex[stageStartY][stageStartX + 2] = 2;

	mapUI->SetMapIndex(mapIndex);
	mapUI->SetPosition({uiView.getSize().x - 110.f, 100.f});

	currentMapSize = maps[0]->GetMapSize();
	worldView.setSize({ currentMapSize.getSize().x * 1.1f, currentMapSize.getSize().y });
	worldView.setCenter(currentMapSize.getSize() * 0.5f);
	isaac->SetPosition(center);

	// LoadStageField("Mapfolder/testmap3.csv");
	mapOffset = sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f;

	for (int i = 0; i < maps.size(); i++)
	{
		maps[i]->SetDoor();
		maps[i]->SetBoundary();
		maps[i]->AddGameObjectInScene();
		if (i > 0)
		{
			maps[i]->AddFly({200.f, 200.f});
			maps[i]->AddFly({250.f, 250.f});
			maps[i]->AddSpider({300.f, 300.f});
			maps[i]->AddSpider({350.f, 350.f});
		}
		if (i > 0)
		{
			maps[i]->SetPosition(maps[i - 1]->GetPosition() + sf::Vector2f(maps[i - 1]->GetMapSize().getSize().x, 0.f));
		}
		maps[i]->SetActiveAll(false);
	}
	maps[0]->SetActiveAll(true);
	maps[0]->SetCleared(true);
	beforeIndex = 0;

	for(auto shading : shadings)
	{
		shading->SetScale({ 2.f, 2.f });
		shading->SetOrigin(sf::Vector2f(TEXTURE_MGR.Get("graphics/shading.png").getSize()) * 0.5f);
		shading->SetPosition(currentMapSize.getSize() * 0.5f);
	}
}

void SceneGame::Update(float dt)
{
	if (beforeIndex != currentMapIndex)
	{
		maps[currentMapIndex]->SetActiveAll(true);
		maps[currentMapIndex]->DeleteEnemyAlreadyDead();
		sf::Vector2f nextMapCenter = maps[currentMapIndex]->GetPosition() + maps[currentMapIndex]->GetMapSize().getSize() * 0.5f;
		if (isMapChanging)
		{
			worldView.setCenter(Utils::Lerp(worldView.getCenter(), nextMapCenter, dt * 15));
			isaac->SetPosition(Utils::Lerp(isaac->GetPosition(), nextSpawnPos, dt * 15));
			if (Utils::Distance(worldView.getCenter(), nextMapCenter) <= 10.f)
			{
				worldView.setCenter(nextMapCenter);
				isaac->SetPosition(nextSpawnPos);
				isMapChanging = false;
			}
		}
		else
		{
			maps[beforeIndex]->SetActiveAll(false);
			beforeIndex = currentMapIndex;
		}
	}
	else
	{
		for (auto &gameObject : gameObjects)
		{
			if (auto player = dynamic_cast<Isaac *>(gameObject))
			{
				isaac = player;
			}
			if (auto monster = dynamic_cast<Monster *>(gameObject))
			{
				monsters.push_back(monster);
			}
		}

		if (isaac)
		{
			sf::Vector2f playerPos = isaac->GetPosition();
			for (auto &monster : monsters)
			{
				monster->SetPlayerPosition(playerPos);
			}
		}

		Scene::Update(dt);

		heartUI->SetHeartCount(isaac->GetCurrentHP());
		heartUI->SetMaxHeartCount(isaac->GetMaxHP());

		if (InputMgr::GetKeyDown(sf::Keyboard::P))
		{
			maps[currentMapIndex]->SetCleared(!maps[currentMapIndex]->GetCleared());
		}

		Map *currentMap = maps[currentMapIndex];
		beforeIndex = currentMapIndex;
		std::vector<Door *> doors = currentMap->GetDoor();
		for (int i = 0; i < doors.size(); i++)
		{
			Door *door = doors[i];
			if (Utils::CheckCollision(isaac->GetHitBoxBody().rect, door->GetHitBox()->rect) && door->GetMapCleared())
			{
				sf::Vector2f dir = door->GetDoorDirection();
				currentYIndex += (int)dir.y;
				currentXIndex += (int)dir.x;
				mapUI->SetPlayerXIndex(currentXIndex);
				mapUI->SetPlayerYIndex(currentYIndex);
				
				isMapChanging = true;
				currentMapIndex = mapIndex[currentYIndex][currentXIndex];
				nextSpawnPos = isaac->GetPosition() + door->GetDoorDirection() * 210.f;
				break;
			}
		}
	}
}

void SceneGame::Draw(sf::RenderWindow &window)
{
	Scene::Draw(window);

	for (int i = 0; i < boundary.size(); i++)
		boundary[i]->Draw(window);
}

void SceneGame::EnemyCollosion()
{
	for (auto &gameObject : gameObjects)
	{
		if (auto player = dynamic_cast<Isaac *>(gameObject))
		{
			isaac = player;
		}
		if (auto monster = dynamic_cast<Monster *>(gameObject))
		{
			monsters.push_back(monster);
		}
	}

	if (isaac)
	{
		sf::Vector2f playerPos = isaac->GetPosition();
		for (auto &monster : monsters)
		{
			monster->SetPlayerPosition(playerPos);
		}
	}
}

std::vector<int> SceneGame::GetNeighboorMapIndex(int x, int y)
{
	int up, right, down, left;

	if (y > 0)
		up = mapIndex[y - 1][x];
	else
		up = -1;

	if (y < 14)
		down = mapIndex[y + 1][x];
	else
		down = -1;

	if (x > 0)
		left = mapIndex[y][x - 1];
	else
		left = -1;

	if (x < 14)
		right = mapIndex[y][x + 1];
	else
		right = -1;

	return std::vector<int>{up, right, down, left};
}
