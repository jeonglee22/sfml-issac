#include "stdafx.h"
#include "Chest.h"
#include "SceneGame.h"

Chest::Chest(const std::string& name)
	: GameObject(name)
{
}

void Chest::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Chest::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Chest::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Chest::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Chest::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Chest::Init()
{
	animator.SetTarget(&sprite);

}

void Chest::Release()
{
}

void Chest::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	switch (chestType)
	{
	case ChestType::Normal:
		animator.Play("animations/chest_normal.csv");
		break;
	case ChestType::Gold:
		animator.Play("animations/chest_gold.csv");
		break;
	}

	SetScale({ 2.0f,2.0f });

	for (auto item : droppedItems)
	{
		if (item)
		{
			item->SetActive(false);
		}
	}
	droppedItems.clear();
	itemVelocities.clear();
	itemsSpawned = false;
	isOpen = false;
}

void Chest::Update(float dt)
{
	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());

	if (itemsSpawned)
	{
		UpdateItemPhysics(dt);
	}
}

void Chest::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	hitBox.Draw(window);
}

void Chest::ChestOpen()
{
	if (isOpen)
	{
		return;
	}

	switch (chestType)
	{
	case ChestType::Normal:
		animator.Play("animations/chest_normal_open.csv");
		break;
	case ChestType::Gold:
		animator.Play("animations/chest_gold_open.csv");
		break;
	}
	isOpen = true;

	SpawnItems();
}

void Chest::SpawnItems()
{
	if (itemsSpawned)
	{
		return;
	}

	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	int itemCount = Utils::RandomRange(2, 3);

	for (int i = 0; i < itemCount; i++)
	{
		Items randomItem;
		int itemTypeRoll = Utils::RandomRange(1, 100);

		if (itemTypeRoll <= 35)
			randomItem = Items::Coin;
		else if (itemTypeRoll <= 55)
			randomItem = Items::Half_Heart;
		else if (itemTypeRoll <= 70)
			randomItem = Items::Heart;
		else if (itemTypeRoll <= 85)
			randomItem = Items::Bomb;
		else
			randomItem = Items::Key;

		float angle = Utils::RandomRange(50.0f, 200.0f) * (3.14159f / 180.0f);
		float speed = Utils::RandomRange(100.0f, 150.0f);

		sf::Vector2f velocity;
		velocity.x = cos(angle) * speed;
		velocity.y = sin(angle) * speed - 150.0f;

		CreateDroppedItem(randomItem, position, velocity);
	}

	itemsSpawned = true;
}

void Chest::CreateDroppedItem(Items itemType, const sf::Vector2f& startPos, const sf::Vector2f& velocity)
{
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	Item* item = new Item("DroppedItem");
	item->SetItemType(itemType);
	item->Init();
	item->Reset();
	item->SetPosition(startPos);
	item->SetOrigin(Origins::MC);

	scene->AddGameObject(item);

	droppedItems.push_back(item);
	itemVelocities.push_back(velocity);

	Map* currentMap = scene->GetCurrentMap();
	if (currentMap) {
		currentMap->AddItemToList(item);
	}
}

void Chest::UpdateItemPhysics(float dt)
{
	const float gravity = 500.0f;
	const float friction = 0.95f;
	const float bounceReduction = 0.4f;

	for (size_t i = 0; i < droppedItems.size(); i++)
	{
		if (i >= itemVelocities.size())
		{
			break;
		}

		Item* item = droppedItems[i];
		if (!item || !item->GetActive())
		{
			continue;
		}

		sf::Vector2f& velocity = itemVelocities[i];
		sf::Vector2f currentPos = item->GetPosition();

		velocity.y += gravity * dt;
		currentPos += velocity * dt;

		float groundY = position.y + 20.0f;
		if (currentPos.y >= groundY && velocity.y > 0)
		{
			currentPos.y = groundY;
			velocity.y *= -bounceReduction;
			velocity.x *= friction;

			if (abs(velocity.y) < 50.0f)
			{
				velocity.y = 0;
			}
			if (abs(velocity.x) < 20.0f)
			{
				velocity.x = 0;
			}
		}

		item->SetPosition(currentPos);
	}
}

bool Chest::IsItemMoving(Item* targetItem)
{
	for (size_t i = 0; i < droppedItems.size(); i++)
	{
		if (droppedItems[i] == targetItem)
		{
			return (abs(itemVelocities[i].x) > 5.0f || abs(itemVelocities[i].y) > 5.0f);
		}
	}
	return false;
}

