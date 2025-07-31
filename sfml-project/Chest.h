#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "Hitbox.h"
#include "Item.h"

class Chest : public GameObject
{
protected:
	sf::Sprite sprite;
	Animator animator;

	ChestType chestType;
	bool isOpen = false;
	HitBox hitBox;

	std::vector<Item*> droppedItems;
	std::vector<sf::Vector2f> itemVelocities;
	std::vector<float> itemCollectibleTimers;
	std::vector<char> itemGrounded;
	bool itemsSpawned = false;

public:
	Chest(const std::string& name = "");
	virtual ~Chest() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	void SetItemType(ChestType type) { chestType = type; }
	void ChestOpen();
	bool IsOpen() { return isOpen; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	HitBox& GetHitBox() { return hitBox; }
	sf::FloatRect GetHitBoxChest()
	{
		sf::FloatRect bodyGlobalBounds = sprite.getGlobalBounds();
		return sprite.getGlobalBounds();
	}

	void SpawnItems();
	void UpdateItemPhysics(float dt);
	const std::vector<Item*>& GetDroppedItems() const { return droppedItems; }

	void CreateDroppedItem(Items itemType, const sf::Vector2f& startPos, const sf::Vector2f& velocity);
	bool IsItemMoving(Item* targetItem);
};

