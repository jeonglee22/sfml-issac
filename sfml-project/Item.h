#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class Item : public GameObject
{
protected:
	sf::Sprite sprite;
	Animator animator;

	Items itemType;
	HitBox hitBox;

	float beatTime = 0.0f;
	bool isLarge = false;

	bool wasGet;

	bool isGetCost = false;
	int cost = 0;
	sf::Sprite* itemCost;
	sf::Vector2f itemCostPos = sf::Vector2f(0, sprite.getLocalBounds().getSize().y + 10.f);

public:
	Item(const std::string& name = "");
	virtual ~Item() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	void SetItemType(Items item) { itemType = item; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetItemGet(bool get) { wasGet = get; }
	bool WasItemGet() const { return wasGet; }

	Items GetItemType()const { return itemType; }
	HitBox& GetHitBox() { return hitBox; }

	void SetItemCost(int cost);
	int GetItemCost() const { return cost; }
	bool IsGetCost() const { return isGetCost; }
};

