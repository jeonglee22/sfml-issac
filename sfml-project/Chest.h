#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "Hitbox.h"

class Chest : public GameObject
{
protected:
	sf::Sprite sprite;
	Animator animator;

	ChestType chestType;

	bool isOpen = false;

	HitBox hitBox;

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

};

