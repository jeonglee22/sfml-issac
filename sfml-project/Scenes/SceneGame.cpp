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
#include "item.h"
#include "MapUI.h"
#include "ItemUI.h"
#include "HeartUI.h"
#include "SkillUI.h"
#include "Skill.h"
#include "MapMaking.h"
#include "TextGo.h"

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
	texIds.push_back("graphics/background/shop.png");
	texIds.push_back("graphics/obstacles/grid_spikes.png");
	texIds.push_back("graphics/obstacles/grid_fireplace.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_basement.png");
	texIds.push_back("graphics/obstacles/pit/grid_pit_basement.png");
	texIds.push_back("graphics/character_001_isaac.png");
	texIds.push_back("graphics/only_tears.png");
	texIds.push_back("graphics/monster_010_fly.png");
	texIds.push_back("graphics/enemies/monster_010_attackfly.png");
	texIds.push_back("graphics/temp_background.png");
	texIds.push_back("graphics/monster_214_level2spider_small.png");
	texIds.push_back("graphics/effects/effect_015_tearpoofa.png");
	texIds.push_back("graphics/additionals/door_01_normaldoor.png");
	texIds.push_back("graphics/additionals/door_01_normaldoor.png");
	texIds.push_back("graphics/shading.png");
	texIds.push_back("graphics/overlay_2.png");
	texIds.push_back("graphics/effect_000_shopkeepers.png");
	texIds.push_back("graphics/effect_002_bloodpoof_large1.png");
	texIds.push_back("graphics/effect_002_bloodpoof.png");
	texIds.push_back("graphics/items/pick ups/pickup_002_coin.png");
	texIds.push_back("graphics/items/pick ups/pickup_001_heart.png");
	texIds.push_back("graphics/items/pick ups/pickup_016_bomb.png");
	texIds.push_back("graphics/items/pick ups/pickup_003_key.png");
	texIds.push_back("graphics/effects/effect_029_explosion.png");
	texIds.push_back("graphics/effects/effect_017_bombradius.png");
	texIds.push_back("graphics/additionals/grid_poop.png");
	texIds.push_back("graphics/monster_044_hopperleaper.png");
	texIds.push_back("graphics/monster_000_bodies02.png");
	texIds.push_back("graphics/additionals/levelitem_001_itemaltar.png");

	texIds.push_back("graphics/enemies/boss_001_larryjr.png");

	texIds.push_back("graphics/minimap.png");
	texIds.push_back("graphics/hudpickups.png");
	texIds.push_back("graphics/ui_hearts.png");
	texIds.push_back("graphics/controls.png");
	texIds.push_back("graphics/ui_chargebar.png");
	texIds.push_back("graphics/additionals/collectibles/collectibles_035_thenecronomicon.png");
	for (int i = 0; i < 10; i++)
		texIds.push_back("fonts/fontimage/" + std::to_string(i) + ".png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	soundIds.push_back("sounds/splatter 2.wav");
	soundIds.push_back("sounds/tear fire 4.wav");
	soundIds.push_back("sounds/tear block.wav");
	soundIds.push_back("sounds/hurt grunt 2.wav");
	soundIds.push_back("sounds/hurt grunt 1.wav");
	soundIds.push_back("sounds/hurt grunt .wav");
	soundIds.push_back("sounds/death burst small.wav");
	soundIds.push_back("sounds/door heavy open.wav");
	soundIds.push_back("sounds/door heavy close.wav");

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
	ANI_CLIP_MGR.Load("animations/attack_fly.csv");
	ANI_CLIP_MGR.Load("animations/fly_dead.csv");
	ANI_CLIP_MGR.Load("animations/spider_patrol.csv");
	ANI_CLIP_MGR.Load("animations/spider_charge.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");
	ANI_CLIP_MGR.Load("animations/spider_jump.csv");
	ANI_CLIP_MGR.Load("animations/blood.csv");
	ANI_CLIP_MGR.Load("animations/blood_small.csv");
	ANI_CLIP_MGR.Load("animations/hopper_idle.csv");
	ANI_CLIP_MGR.Load("animations/hopper_jump.csv");
	ANI_CLIP_MGR.Load("animations/body_front.csv");
	ANI_CLIP_MGR.Load("animations/body_side.csv");

	ANI_CLIP_MGR.Load("animations/tears_idle.csv");
	ANI_CLIP_MGR.Load("animations/tears_boom.csv");

	ANI_CLIP_MGR.Load("animations/coin.csv");
	ANI_CLIP_MGR.Load("animations/heart.csv");
	ANI_CLIP_MGR.Load("animations/half_heart.csv");
	ANI_CLIP_MGR.Load("animations/bomb.csv");
	ANI_CLIP_MGR.Load("animations/key.csv");

	ANI_CLIP_MGR.Load("animations/explosion.csv");
	ANI_CLIP_MGR.Load("animations/bombradius.csv");

	ANI_CLIP_MGR.Load("animations/boss_larry_jr_head_front.csv");
	ANI_CLIP_MGR.Load("animations/boss_larry_jr_head_rare.csv");
	ANI_CLIP_MGR.Load("animations/boss_larry_jr_head_side.csv");
	ANI_CLIP_MGR.Load("animations/boss_larry_jr_body1.csv");
	ANI_CLIP_MGR.Load("animations/boss_larry_jr_body2.csv");
	ANI_CLIP_MGR.Load("animations/boss_larry_jr_body3.csv");
	ANI_CLIP_MGR.Load("animations/boss_larry_jr_tail.csv");

	isaac = (Isaac *)AddGameObject(new Isaac());

	std::vector<MapMaking::MapType> mapTypes;
	sf::Vector2i startPos = MapMaking::MapRandomMaking(10, mapIndex, mapTypes);
	stageStartX = currentXIndex = startPos.x;
	stageStartY = currentYIndex = startPos.y;

	maps = MapMaking::SetMapInfo(mapIndex, 10, mapTypes);
	for (auto& map : maps)
		AddGameObject(map);

	for(int i =0; i <1;i++)
	{
		shadings.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/shading.png")));

		shadings[i]->sortingLayer = SortingLayers::Background;
		shadings[i]->sortingOrder = 20;
	}
	controls = (SpriteGo*)AddGameObject(new SpriteGo("graphics/controls.png"));
	controls->sortingLayer = SortingLayers::Background;
	controls->sortingOrder = 5;

	mapUI = (MapUI*)AddGameObject(new MapUI("graphics/minimap.png", "mapUI"));
	mapUI->SetPlayerXIndex(startPos.x);
	mapUI->SetPlayerYIndex(startPos.y);
	itemUI = (ItemUI*)AddGameObject(new ItemUI("ItemUI"));
	heartUI = (HeartUI*)AddGameObject(new HeartUI("graphics/ui_hearts.png", "HeartUI"));
	skillUI = (SkillUI*)AddGameObject(new SkillUI("graphics/ui_chargebar.png", "SkillUI"));
	skill = new Skill("graphics/additionals/collectibles/collectibles_035_thenecronomicon.png", "necronomicon");
	skill->SetSkillFunc([this]() {
		for (auto monster : monsters)
		{
			if (!monster->GetActive() || monster->IsDead())
			{
				continue;
			}
				monster->TakeDamage(40);

		}
	});
	skill->SetTotalSkillCooltime(4);

	FPS = (TextGo*)AddGameObject(new TextGo("fonts/DS-DIGIT.ttf", "frame"));
	FPS->SetCharacterSize(30);
	FPS->SetOrigin(Origins::MC);
	FPS->sortingLayer = SortingLayers::UI;
	FPS->sortingOrder = 50;

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

	mapUI->SetScale({ 2.f,2.f });
	itemUI->SetScale({ 2.f,2.f });
	heartUI->SetScale({ 2.f,2.f });

	mapUI->SetMapIndex(mapIndex);
	mapUI->SetPosition({ uiView.getSize().x - 110.f, 100.f });

	currentMapSize = smallMapSize = maps[0]->GetMapSize();
	
	// LoadStageField("Mapfolder/testmap3.csv");
	mapOffset = sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f;

	MapMaking::SetMapConnection(maps);

	worldView.setSize({ currentMapSize.getSize().x * 1.1f, currentMapSize.getSize().y });
	worldView.setCenter(maps[0]->GetPosition() + currentMapSize.getSize() * 0.5f);
	isaac->SetPosition(worldView.getCenter());

	beforeIndex = 0;

	for (auto shading : shadings)
	{
		shading->SetScale({ 2.f, 2.f });
		shading->SetOrigin(sf::Vector2f(TEXTURE_MGR.Get("graphics/shading.png").getSize()) * 0.5f);
		shading->SetPosition(worldView.getCenter());
	}
	controls->SetScale({ 2.f,2.f });
	controls->SetOrigin(sf::Vector2f(TEXTURE_MGR.Get("graphics/controls.png").getSize()) * 0.5f);
	controls->SetPosition(worldView.getCenter());

	isaac->SetSkill(skill);
	skillUI->SetSkill(isaac->GetSkill());
	skillUI->SetPosition({ 60.f,60.f });

	FPS->SetPosition({150.f, 50.f});
}

void SceneGame::Update(float dt)
{
	SOUND_MGR.SetSfxVolume(20);

	FPSTime += dt;
	if (FPSTime >= 1.f)
	{
		FPS->SetString("FPS : " + std::to_string(1 / dt));
		FPSTime = 0.f;
	}

	printTime += dt;

	if (beforeIndex != currentMapIndex)
	{
		maps[currentMapIndex]->SetActiveAll(true);
		maps[currentMapIndex]->DeleteEnemyAlreadyDead();
		maps[currentMapIndex]->DeleteItemAlreadyGet();
		if (isMapChanging)
		{
			worldView.setCenter(Utils::Lerp(worldView.getCenter(), nextMapViewStart, dt * 15));
			isaac->SetPosition(Utils::Lerp(isaac->GetPosition(), nextSpawnPos, dt * 15));
			if (Utils::Distance(worldView.getCenter(), nextMapViewStart) <= 1.f)
			{
				worldView.setCenter(nextMapViewStart);
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

		ViewFollowing();

		heartUI->SetHeartCount(isaac->GetCurrentHP());
		heartUI->SetMaxHeartCount(isaac->GetMaxHP());

		if(isaac->GetBombCount() != itemUI->GetBombCount())
			itemUI->SetItemUICount(Items::Bomb, isaac->GetBombCount());

		if (isaac && !isMapChanging)
		{
			Map* currentMap = maps[currentMapIndex];
			auto items = currentMap->GetItems();

			for (auto item : items)
			{
				if (item->GetActive() && Utils::CheckCollision(isaac->GetHitBoxBody().rect, item->GetHitBox().rect))
				{
					isaac->AddItem(item->GetItemType());
					itemUI->SetItemUICount(item->GetItemType(), itemUI->GetItemUICount(item->GetItemType()) + 1);
					item->SetActive(false);
					item->SetItemGet(true);
				}
			}
		}

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
				nextMapViewStart = worldView.getCenter() + sf::Vector2f(smallMapSize.getSize().x * dir.x, smallMapSize.getSize().y * dir.y);

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

	if (y < 10)
		down = mapIndex[y + 1][x];
	else
		down = -1;

	if (x > 0)
		left = mapIndex[y][x - 1];
	else
		left = -1;

	if (x < 10)
		right = mapIndex[y][x + 1];
	else
		right = -1;

	return std::vector<int>{up, right, down, left};
}

sf::Vector2i SceneGame::GetNeighboorMapIndexInLargeMap(int x, int y)
{
	if (mapIndex[y - 1][x] == mapIndex[y][x])
		return sf::Vector2i(x, y-1);
	else if (mapIndex[y][x-1] == mapIndex[y][x])
		return sf::Vector2i(x-1, y);
	return sf::Vector2i();
}

void SceneGame::AddSkillCooltimeAtClear()
{
	Skill* skill = isaac->GetSkill();
	skill->AddSkillCooltime();
}

void SceneGame::ViewFollowing()
{
	Map* currentMap = maps[currentMapIndex];
	currentMapSize = currentMap->GetMapSize();
	sf::FloatRect viewBoundary;
	viewBoundary.left = 0; 
	viewBoundary.top = 0;
	viewBoundary.width = currentMapSize.width - smallMapSize.width;
	viewBoundary.height = currentMapSize.height - smallMapSize.height;
	/*std::cout << viewBoundary.left << ", " << viewBoundary.top << ", ";
	std::cout << viewBoundary.width << ", " << viewBoundary.height << std::endl;*/

	sf::Vector2f center;
	float centerXMin = viewBoundary.left + currentMap->GetPosition().x + smallMapSize.getSize().x * 0.5f;
	float centerXMax = viewBoundary.left + viewBoundary.width + currentMap->GetPosition().x + smallMapSize.getSize().x * 0.5f;
	float centerYMin = viewBoundary.top + currentMap->GetPosition().y + smallMapSize.getSize().y * 0.5f;
	float centerYMax = viewBoundary.top + viewBoundary.height + currentMap->GetPosition().y + smallMapSize.getSize().y * 0.5f;
	center.x = Utils::Clamp(isaac->GetPosition().x, centerXMin, centerXMax);
	center.y = Utils::Clamp(isaac->GetPosition().y, centerYMin, centerYMax);

	worldView.setCenter(center );

	if(printTime >= 1.f)
	{
		std::cout << worldView.getCenter().x << ", " << worldView.getCenter().y << std::endl;
		std::cout << isaac->GetPosition().x << ", " << isaac->GetPosition().y << std::endl;
		std::cout << currentMap->GetPosition().x << ", " << currentMap->GetPosition().y << std::endl;
		printTime = 0.f;
	}
}
