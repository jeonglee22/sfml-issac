#include "stdafx.h"
#include "rapidcsv.h"
#include "Map.h"
#include "Fly.h"
#include "Spider.h"
#include "Hopper.h"
#include "Door.h"
#include "SceneGame.h"
#include "Obstacles.h"
#include "SpriteGo.h"
#include "Spikes.h"
#include "Monster.h"
#include "Item.h"
#include "HitBox.h"
#include "Body.h"
#include "AttackFly.h"
#include "LarryJr.h"
#include "Horf.h"
#include "Pooter.h"
#include "Dip.h"
#include "Dingle.h"
#include "ItemAltar.h"
#include "Mulligan.h"
#include "Chest.h"

Map::Map(const std::string &filePath, const std::string &name, const MapType ty)
	: filePath(filePath), GameObject(name), type(ty)
{
}

void Map::SetPosition(const sf::Vector2f &pos)
{
	GameObject::SetPosition(pos);
	center.setPosition(pos);
	for (auto monster : monsters)
		monster->SetPosition(monster->GetPosition() + pos);
	for (auto door : doors)
		door->SetPosition(door->GetPosition() + pos);
	for (auto boundary : boundary)
		boundary->rect.setPosition(boundary->rect.getPosition() + pos);
	for (auto tearboundary : tearBoundary)
		tearboundary->rect.setPosition(tearboundary->rect.getPosition() + pos);
	for (auto spike : spikes)
		spike->SetPosition(spike->GetPosition() + pos);
	for (auto obstacle : obstacles)
		obstacle->SetPosition(obstacle->GetPosition() + pos);
	for (auto ground : backgrounds)
		ground->SetPosition(ground->GetPosition() + pos);
	for (auto item : items)
		item->SetPosition(item->GetPosition() + pos);
	for (auto chest : chests)
		chest->SetPosition(chest->GetPosition() + pos);
}

void Map::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	center.setRotation(rot);
}

void Map::SetScale(const sf::Vector2f &s)
{
	GameObject::SetScale(s);
	center.setScale(s);
}

void Map::SetOrigin(const sf::Vector2f &o)
{
	GameObject::SetOrigin(o);
	center.setOrigin(o);
}

void Map::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(center, preset);
	}
}

void Map::Init()
{
}

void Map::Release()
{
}

void Map::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
	{
		sceneGame = (SceneGame *)SCENE_MGR.GetCurrentScene();
		LoadStageField(filePath);
	}
}

void Map::Update(float dt)
{
	if (CheckAllEnemyDead())
	{
		SetCleared(true);
	}
	else
	{
		SetCleared(false);
	}
}

void Map::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < boundary.size(); i++)
	{
		boundary[i]->Draw(window);
	}
	for (int i = 0; i < tearBoundary.size(); i++)
	{
		tearBoundary[i]->Draw(window);
	}
}

void Map::SetCleared(bool b)
{
	if (b && !isCleared)
	{
		sceneGame->AddSkillCooltimeAtClear();
		SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/door heavy open.wav"));
	}
	if (!b && isCleared)
	{
		SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/door heavy close.wav"));
	}
	isCleared = b;
	for (auto door : doors)
	{
		if(!door->GetDoorLocked() && !door->GetDoorHidden())
			door->SetMapCleared(b);
	}
}

void Map::AddMonster(const sf::Vector2f &pos, const std::string &name)
{
	Monster *monster;
	if (name == "monster_214_level2spider_small")
		monster = new Spider();
	else if (name == "monster_010_fly")
		monster = new Fly();
	else if (name == "monster_010_attackfly")
		monster = new AttackFly();
	else if (name == "monster_000_bodies02")
		monster = new Body();
	else if (name == "monster_029_horf")
		monster = new Horf();
	else if (name == "monster_001_pooter")
		monster = new Pooter();
	else if (name == "monster_216_dip")
		monster = new Dip();
	else if (name == "monster_054_mulligan")
		monster = new Mulligan();
	else if (name == "boss_085_dingle")
		monster = new Dingle();
	else if (name == "boss_001_larryjr")
		monster = new LarryJr();
	else if (name == "monster_044_hopperleaper")
		monster = new Hopper();
	monsters.push_back(monster);
	monster->Init();
	monster->Reset();
	monster->SetPosition(pos + sf::Vector2f(currentMapRect.left, currentMapRect.top) * -1.f);
	sceneGame->AddGameObject(monster);
}

void Map::AddItem(const sf::Vector2f &pos, const std::string &name)
{
	Item *item = new Item();
	items.push_back(item);
	item->Init();
	if (name == "heart")
		item->SetItemType(Items::Heart);
	else if (name == "halfheart")
		item->SetItemType(Items::Half_Heart);
	else if (name == "pickup_002_coin")
		item->SetItemType(Items::Coin);
	else if (name == "pickup_016_bomb")
		item->SetItemType(Items::Bomb);
	else if (name == "pickup_003_key")
		item->SetItemType(Items::Key);
	item->Reset();
	item->SetPosition(pos + sf::Vector2f(currentMapRect.left, currentMapRect.top) * -1.f);
	sceneGame->AddGameObject(item);
}

void Map::AddChest(const sf::Vector2f& pos, const std::string& name)
{
	Chest* chest = new Chest();
	chests.push_back(chest);
	chest->Init();
	if (name == "chests")
		chest->SetItemType(ChestType::Normal);
	else if (name == "chests_gold")
		chest->SetItemType(ChestType::Gold);
	chest->Reset();
	chest->SetPosition(pos + sf::Vector2f(currentMapRect.left, currentMapRect.top) * -1.f);
	sceneGame->AddGameObject(chest);
}

void Map::SetDoor()
{
	std::vector<sf::Vector2i> posDiffer;
	sf::Vector2f currentMapSize = currentMapRect.getSize();
	std::vector<int> neighboorMapIndex = sceneGame->GetNeighboorMapIndex(StageXPos, StageYPos);
	int currentMapIndex = sceneGame->GetMapIndex(StageXPos, StageYPos);
	if (name == "RectangleMap")
	{
		posDiffer.push_back(sceneGame->GetNeighboorMapIndexInRectangleMap(StageXPos, StageYPos) - sf::Vector2i(StageXPos, StageYPos));
		for (int i : sceneGame->GetNeighboorMapIndex(posDiffer[0].x + StageXPos, posDiffer[0].y + StageYPos))
		{
			neighboorMapIndex.push_back(i);
		}
	}
	else if (name == "LargeMap")
	{
		posDiffer.push_back({ -1,0 });
		posDiffer.push_back({ 0,-1 });
		posDiffer.push_back({ -1,-1 });
		for (int i = 0; i < 3; i++)
		{
			for (auto index : sceneGame->GetNeighboorMapIndex(posDiffer[i].x + StageXPos, posDiffer[i].y + StageYPos))
				neighboorMapIndex.push_back(index);
		}
	}
	float width = sceneGame->GetSmallMapSize().width, height = sceneGame->GetSmallMapSize().height;
	Door tempdoor = Door(MapType::Normal, "Door");
	tempdoor.Init();
	tempdoor.Reset();

	sf::Vector2f centerPos;
	if (posDiffer.size() == 0)
		centerPos = currentMapSize * 0.5f;
	if (posDiffer.size() == 1)
		centerPos = currentMapSize * 0.5f + sf::Vector2f(currentMapSize.x * 0.25f * (-posDiffer[0].x), currentMapSize.y * 0.25f * (-posDiffer[0].y));
	if (posDiffer.size() == 3)
		centerPos = currentMapSize * 0.75f;

	for(int i = 0; i < posDiffer.size()+1; i++)
	{
		sf::Vector2f differPos;
		if (i > 0)
		{
			differPos.x = posDiffer[i-1].x * width;
			differPos.y = posDiffer[i-1].y * height;
		}
		for (int j = 0; j < 4; j++)
		{
			sf::Vector2f localPos;
			localPos.x = (width * 0.5f - 104.f) * (j % 2 == 1 ? 2.f - j : 0.f);
			localPos.y = (height * 0.5f - 104.f) * (j % 2 == 0 ? j - 1.f : 0.f);
			if (neighboorMapIndex[i * 4 + j] == currentMapIndex)
			{
				continue;
			}
			else if (neighboorMapIndex[i * 4 + j] != -1 && neighboorMapIndex[i * 4 + j] != 99)
			{
				Door* door = nullptr;
				if( sceneGame->GetMapTypes()[currentMapIndex] != MapType::Normal &&
					sceneGame->GetMapTypes()[currentMapIndex] != MapType::Special &&
					sceneGame->GetMapTypes()[currentMapIndex] != MapType::Large &&
					sceneGame->GetMapTypes()[currentMapIndex] != MapType::Rectangle &&
					sceneGame->GetMapTypes()[currentMapIndex] != MapType::Start)
				{
					door = new Door(sceneGame->GetMapTypes()[currentMapIndex], "Door");
					if (sceneGame->GetMapTypes()[neighboorMapIndex[i * 4 + j]] == MapType::Hidden)
					{
						door->SetDoorHidden(true);
					}
				}
				else
				{
					door = new Door(sceneGame->GetMapTypes()[neighboorMapIndex[i * 4 + j]], "Door");
					if (sceneGame->GetMapTypes()[neighboorMapIndex[i * 4 + j]] == MapType::Shop)
					{
						door->SetDoorLocked(true);
					}
					else if (sceneGame->GetMapTypes()[neighboorMapIndex[i * 4 + j]] == MapType::Treasure)
					{
						if (Utils::RandomRange(0.f,1.f) <= 0.5f)
							door->SetDoorLocked(true);
					}
					else if (sceneGame->GetMapTypes()[neighboorMapIndex[i * 4 + j]] == MapType::Hidden)
					{
						door->SetDoorHidden(true);
					}
				}
				door->Init();
				door->Reset();
				door->SetPosition(centerPos + localPos + differPos);
				door->SetRotation(90.f * j);
				door->SetDoorDirection(j);
				doors.push_back(door);
			}
			else
			{
				HitBox* doorBoundaryBox = new HitBox();
				doorBoundaryBox->rect.setSize((sf::Vector2f)tempdoor.GetSprite().getTextureRect().getSize());
				doorBoundaryBox->rect.setOrigin({ doorBoundaryBox->rect.getSize().x * 0.5f, doorBoundaryBox->rect.getSize().y });
				doorBoundaryBox->rect.setPosition(centerPos + localPos + differPos);
				doorBoundaryBox->rect.setRotation(90.f * j);
				doorBoundary.push_back(doorBoundaryBox);
			}
		}
	}
	for (auto bound : doorBoundary)
		boundary.push_back(bound);
}

void Map::SetBoundary()
{
	float left = currentMapRect.left, top = currentMapRect.top, width = currentMapRect.width, height = currentMapRect.height;
	Door tempdoor = Door(MapType::Normal, "Door");
	tempdoor.Init();
	tempdoor.Reset();
	sf::Vector2f doorSize = (sf::Vector2f)tempdoor.GetSprite().getTextureRect().getSize();
	int boundaryCount = boundary.size();

	sf::Vector2f Bound = { (sceneGame->GetSmallMapSize().width - doorSize.x) * 0.5f, 104.f};

	for (int i = 0; i < doorBoundary.size(); i++)
	{
		boundary.push_back(new HitBox());
		boundary.push_back(new HitBox());

		for(int j = 0; j < 2; j++)
		{
			boundary[i * 2 + j + boundaryCount]->rect.setSize(Bound);
			boundary[i * 2 + j + boundaryCount]->rect.setOrigin({ j == 0 ? Bound.x + doorSize.x * 0.5f : -doorSize.x * 0.5f, 104.f });
			boundary[i * 2 + j + boundaryCount]->rect.setRotation(doorBoundary[i]->rect.getRotation());
			boundary[i * 2 + j + boundaryCount]->rect.setPosition(doorBoundary[i]->rect.getPosition());
		}

		HitBox* tearBox = new HitBox();
		tearBox->rect.setSize({ sceneGame->GetSmallMapSize().width, 50.f });
		tearBox->rect.setOrigin({ tearBox->rect.getSize().x * 0.5f, 104.f });
		tearBox->rect.setRotation(doorBoundary[i]->rect.getRotation());
		tearBox->rect.setPosition(doorBoundary[i]->rect.getPosition());
		tearBoundary.push_back(tearBox);
	}
	boundaryCount = boundary.size();
	for (int i = 0; i < doors.size(); i++)
	{
		boundary.push_back(new HitBox());
		boundary.push_back(new HitBox());

		for (int j = 0; j < 2; j++)
		{
			boundary[i * 2 + j + boundaryCount]->rect.setSize(Bound);
			boundary[i * 2 + j + boundaryCount]->rect.setOrigin({ j == 0 ? Bound.x + doorSize.x * 0.5f : -doorSize.x * 0.5f, 104.f });
			boundary[i * 2 + j + boundaryCount]->rect.setRotation(doors[i]->GetRotation());
			boundary[i * 2 + j + boundaryCount]->rect.setPosition(doors[i]->GetPosition());
		}

		HitBox* tearBox = new HitBox();
		tearBox->rect.setSize({ sceneGame->GetSmallMapSize().width, 50.f });
		tearBox->rect.setOrigin({ sceneGame->GetSmallMapSize().width * 0.5f , 104.f});
		tearBox->rect.setRotation(doors[i]->GetRotation());
		tearBox->rect.setPosition(doors[i]->GetPosition());
		tearBoundary.push_back(tearBox);
	}
}

void Map::ClearSprites()
{
	monsters.clear();
	obstacles.clear();
	doors.clear();
	spikes.clear();
	backgrounds.clear();
}

void Map::LoadStageField(const std::string &filePath)
{
	rapidcsv::Document doc(filePath);

	currentMapRect = sf::FloatRect(doc.GetCell<float>(0, 0), doc.GetCell<float>(1, 0), doc.GetCell<float>(2, 0), doc.GetCell<float>(3, 0));

	ClearSprites();
	for (int i = 0; i < doc.GetRowCount() - 1; i++)
	{
		std::vector<std::string> infos = doc.GetRow<std::string>(i + 1);
		CreateMatchedTypeGO(infos);
	}
}

void Map::CreateMatchedTypeGO(const std::vector<std::string> infos)
{
	if (infos[5] == "rocks_basement" || infos[5] == "grid_pit_basement")
	{
		obstacles.push_back(new Obstacles(infos[0], infos[5]));
		SpriteSetting(obstacles[obstacles.size() - 1], infos);
		allObjects.push_back(obstacles[obstacles.size() - 1]);
	}
	else if (infos[5] == "grid_spikes")
	{
		spikes.push_back(new Spikes(infos[0], infos[5]));
		SpriteSetting(spikes[spikes.size() - 1], infos);
		allObjects.push_back(spikes[spikes.size() - 1]);
	}
	else if (infos[5].substr(0,5) == "level")
	{
		obstacles.push_back(new ItemAltar(infos[0], infos[5]));
		SpriteSetting(obstacles[obstacles.size() - 1], infos);
		allObjects.push_back(obstacles[obstacles.size() - 1]);
	}
	else if (infos[5].substr(0, 4) == "mons" || infos[5].substr(0, 4) == "boss")
	{
		AddMonster({std::stof(infos[6]), std::stof(infos[7])}, infos[5]);
	}
	else if (infos[5].substr(0, 4) == "pick" || infos[5] == "heart" || infos[5] == "halfheart")
	{
		AddItem({std::stof(infos[6]), std::stof(infos[7])}, infos[5]);
	}
	else if (infos[5] == "chests" || infos[5] == "chests_gold")
	{
		AddChest({ std::stof(infos[6]), std::stof(infos[7]) }, infos[5]);
	}
	else
	{
		backgrounds.push_back(new SpriteGo(infos[0], infos[5]));
		SpriteSetting(backgrounds[backgrounds.size() - 1], infos);
		sf::Color spriteColor = backgrounds[backgrounds.size() - 1]->GetSprite().getColor();
		backgrounds[backgrounds.size() - 1]->GetSprite().setColor(sf::Color(spriteColor.r * 0.7, spriteColor.g * 0.7, spriteColor.b * 0.7, spriteColor.a));
	}
}

void Map::SpriteSetting(SpriteGo *sp, const std::vector<std::string> infos)
{
	sp->Init();
	sp->SetOrigin(Origins::MC);
	sp->Reset();
	sp->GetSprite().setTextureRect({std::stoi(infos[2]), std::stoi(infos[1]), std::stoi(infos[3]), std::stoi(infos[4])});
	sp->SetScale({2.f * std::stof(infos[15]), 2.f * std::stof(infos[16])});
	sp->SetOrigin({std::stof(infos[13]), std::stof(infos[14])});
	sp->SetPosition(sf::Vector2f(std::stof(infos[6]), std::stof(infos[7])) + sf::Vector2f(currentMapRect.left, currentMapRect.top) * -1.f);
	sp->SetRotation(std::stof(infos[12]));
	sp->sortingLayer = (SortingLayers)std::stoi(infos[10]);
	sp->sortingOrder = std::stoi(infos[11]);
}

void Map::AddGameObjectInScene()
{
	for (auto monster : monsters)
		sceneGame->AddGameObject(monster);
	for (auto door : doors)
		sceneGame->AddGameObject(door);
	for (auto spike : spikes)
		sceneGame->AddGameObject(spike);
	for (auto obstacle : obstacles)
		sceneGame->AddGameObject(obstacle);
	for (auto ground : backgrounds)
		sceneGame->AddGameObject(ground);
	for (auto item : items)
		sceneGame->AddGameObject(item);
	for (auto chest : chests)
		sceneGame->AddGameObject(chest);

}

void Map::SetActiveAll(bool b)
{
	for (auto monster : monsters)
		monster->SetActive(b);
	for (auto door : doors)
		door->SetActive(b);
	for (auto spike : spikes)
		spike->SetActive(b);
	for (auto obstacle : obstacles)
		obstacle->SetActive(b);
	for (auto ground : backgrounds)
		ground->SetActive(b);
	for (auto item : items)
		item->SetActive(b);
	for (auto chest : chests)
		chest->SetActive(b);
}

bool Map::CheckAllEnemyDead()
{
	bool allDead = true;
	for (auto monster : monsters)
	{
		if (monster->GetActive())
			allDead = false;
	}
	return allDead;
}

void Map::DeleteEnemyAlreadyDead()
{
	for (auto monster : monsters)
	{
		if (monster->GetCurrentHP() <= 0)
			monster->SetActive(false);
	}
}

void Map::DeleteItemAlreadyGet()
{
	for (auto item : items)
	{
		if (item->WasItemGet())
		{
			item->SetActive(false);
		}
	}
}
