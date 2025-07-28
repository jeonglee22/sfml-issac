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

Map::Map(const std::string &filePath, const std::string &name)
	: filePath(filePath), GameObject(name)
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
	for (auto spike : spikes)
		spike->SetPosition(spike->GetPosition() + pos);
	for (auto obstacle : obstacles)
		obstacle->SetPosition(obstacle->GetPosition() + pos);
	for (auto ground : backgrounds)
		ground->SetPosition(ground->GetPosition() + pos);
	for (auto item : items)
		item->SetPosition(item->GetPosition() + pos);

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
		boundary[i]->Draw(window);
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
		door->SetMapCleared(b);
	}
}

void Map::AddMonster(const sf::Vector2f &pos, const std::string& name)
{
	Monster* monster;
	if (name == "monster_214_level2spider_small")
		monster = new Spider();
	else if (name == "monster_010_fly")
		monster = new Fly();
	else if (name == "monster_000_bodies02")
		monster = new Body();
	else if (name == "monster_044_hopperleaper")
		monster = new Hopper();
	monsters.push_back(monster);
	monster->Init();
	monster->Reset();
	monster->SetPosition(pos + sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f);
	sceneGame->AddGameObject(monster);
}

void Map::AddItem(const sf::Vector2f& pos, const std::string& name)
{
	Item* item = new Item();
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
	item->SetPosition(pos + sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f);
	sceneGame->AddGameObject(item);
}

void Map::SetDoor()
{
	std::vector<int> neighboorMapIndex = sceneGame->GetNeighboorMapIndex(StageXPos, StageYPos);
	float width = currentMapSize.width, height = currentMapSize.height;
	Door tempdoor = Door("graphics/additionals/door_01_normaldoor.png", "Door");
	tempdoor.Reset();
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f localPos;
		localPos.x = (width * 0.5f - 104.f) * (i % 2 == 1 ? 2.f - i : 0.f);
		localPos.y = (height * 0.5f - 104.f) * (i % 2 == 0 ? i - 1.f : 0.f);
		if(neighboorMapIndex[i] != -1 && neighboorMapIndex[i] != 99)
		{
			doors.push_back(new Door("graphics/additionals/door_01_normaldoor.png", "Door"));
			doors[doors.size() - 1]->Init();
			doors[doors.size() - 1]->Reset();
			doors[doors.size() - 1]->SetPosition(currentMapSize.getSize() * 0.5f + localPos);
			doors[doors.size() - 1]->SetRotation(90.f * i);
			doors[doors.size() - 1]->SetDoorDirection(i);
		}
		else
		{
			boundary.push_back(new HitBox());
			boundary[boundary.size() - 1]->rect.setSize((sf::Vector2f)tempdoor.GetSprite().getTextureRect().getSize());
			boundary[boundary.size() - 1]->rect.setOrigin({ boundary[boundary.size() - 1]->rect.getSize().x * 0.5f,
				boundary[boundary.size() - 1]->rect.getSize().y});
			boundary[boundary.size() - 1]->rect.setPosition(currentMapSize.getSize() * 0.5f + localPos);
			boundary[boundary.size() - 1]->rect.setRotation(90.f * i);
		}
	}
	std::cout << std::endl;
}

void Map::SetBoundary()
{
	float left = currentMapSize.left, top = currentMapSize.top, width = currentMapSize.width, height = currentMapSize.height;
	Door tempdoor = Door("graphics/additionals/door_01_normaldoor.png", "Door");
	tempdoor.Reset();
	sf::Vector2f doorSize = (sf::Vector2f)tempdoor.GetSprite().getTextureRect().getSize();
	int nonDoorCount = boundary.size();
	for (int i = 0; i < 4; i++)
	{
		boundary.push_back(new HitBox());
		boundary.push_back(new HitBox());
		if (i < 2)
		{
			// boundary[i]->rect.setSize({ currentMapSize.width, 104.f });
			sf::Vector2f rowBound = {(currentMapSize.width - doorSize.x) * 0.5f, 104.f};
			boundary[i * 2 + nonDoorCount]->rect.setSize(rowBound);
			boundary[i * 2 + 1 + nonDoorCount]->rect.setSize(rowBound);
			boundary[i * 2 + nonDoorCount]->rect.setOrigin({rowBound.x + doorSize.x * 0.5f, 52.f});
			boundary[i * 2 + 1 + nonDoorCount]->rect.setOrigin({-doorSize.x * 0.5f, 52.f});
		}
		else
		{
			// boundary[i]->rect.setSize({ 104.f, currentMapSize.height });
			sf::Vector2f colBound = {104.f, (currentMapSize.height - doorSize.x) * 0.5f};
			boundary[i * 2 + nonDoorCount]->rect.setSize(colBound);
			boundary[i * 2 + 1 + nonDoorCount]->rect.setSize(colBound);
			boundary[i * 2 + nonDoorCount]->rect.setOrigin({52.f, colBound.y + doorSize.x * 0.5f});
			boundary[i * 2 + 1 + nonDoorCount]->rect.setOrigin({52.f, -doorSize.x * 0.5f});
		}
	}
	boundary[nonDoorCount]->rect.setPosition({currentMapSize.getSize().x * 0.5f, 52.f});
	boundary[1 + nonDoorCount]->rect.setPosition({currentMapSize.getSize().x * 0.5f, 52.f});
	boundary[2 + nonDoorCount]->rect.setPosition({currentMapSize.getSize().x * 0.5f, currentMapSize.getSize().y - 52.f});
	boundary[3 + nonDoorCount]->rect.setPosition({currentMapSize.getSize().x * 0.5f, currentMapSize.getSize().y - 52.f});
	boundary[4 + nonDoorCount]->rect.setPosition({52.f, currentMapSize.getSize().y * 0.5f});
	boundary[5 + nonDoorCount]->rect.setPosition({52.f, currentMapSize.getSize().y * 0.5f});
	boundary[6 + nonDoorCount]->rect.setPosition({currentMapSize.getSize().x - 52.f, currentMapSize.getSize().y * 0.5f});
	boundary[7 + nonDoorCount]->rect.setPosition({currentMapSize.getSize().x - 52.f, currentMapSize.getSize().y * 0.5f});
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

	currentMapSize = sf::FloatRect(doc.GetCell<float>(0, 0), doc.GetCell<float>(1, 0), doc.GetCell<float>(2, 0), doc.GetCell<float>(3, 0));

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
	else if (infos[5].substr(0, 4) == "mons")
	{
		AddMonster({ std::stof(infos[6]),std::stof(infos[7]) }, infos[5]);
	}
	else if (infos[5].substr(0, 4) == "pick" || infos[5] == "heart" || infos[5] == "halfheart")
	{
		AddItem({ std::stof(infos[6]),std::stof(infos[7]) }, infos[5]);
	}
	else
	{
		backgrounds.push_back(new SpriteGo(infos[0], infos[5]));
		SpriteSetting(backgrounds[backgrounds.size() - 1], infos);
	}
}

void Map::SpriteSetting(SpriteGo *sp, const std::vector<std::string> infos)
{
	sp->Init();
	sp->SetOrigin(Origins::MC);
	sp->Reset();
	sp->GetSprite().setTextureRect({std::stoi(infos[2]), std::stoi(infos[1]), std::stoi(infos[3]), std::stoi(infos[4])});
	sp->SetScale({2.f, 2.f});
	sp->SetOrigin({std::stof(infos[13]), std::stof(infos[14])});
	sp->SetPosition(sf::Vector2f(std::stof(infos[6]), std::stof(infos[7])) + sf::Vector2f(currentMapSize.left, currentMapSize.top) * -1.f);
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
