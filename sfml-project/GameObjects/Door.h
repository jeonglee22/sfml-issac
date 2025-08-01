#pragma once
#include "SpriteGo.h"
#include "HitBox.h"
#include "Animator.h"

class Door : public SpriteGo
{
protected:
	sf::Sprite doorClosedLeft;
	sf::Sprite doorClosedRight;
	sf::Sprite doorOpened;
	sf::IntRect doorOpenedRect = { 84, 16, 25, 23 };
	sf::IntRect doorClosedRightRect = { 84,64,25,23 };
	sf::IntRect doorClosedLeftRect = { 19,64,25,23 };

	sf::IntRect doorTextureRect;

	HitBox* hitBox = nullptr;

	bool isCleared = false;
	bool isLocked = false;
	bool isStartKeyAnimation = false;

	sf::Vector2f doorOffset = { 0.f,0.f };
	sf::Vector2f keyOffset = { 0.f,-18.f };

	sf::Vector2f doorDirection;

	Animator* animator;
	sf::Sprite* key = nullptr;

	float keyPlayingTime = 0.f;
	float keyPlayingTimeMax = 1.2f;

	MapType type;

public:
	Door(MapType type = MapType::None, const std::string& name = "");
	virtual ~Door() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	HitBox* GetHitBox() const { return hitBox; }
	MapType GetDoorType() const { return type; }
	void SetDoorLocked(bool b) { isLocked = b; }
	bool GetDoorLocked() const { return isLocked; }
	bool GetMapCleared() const { return isCleared; }
	void SetMapCleared(bool b) { isCleared = b; }
	sf::Vector2i GetDoorSize() const { return doorOpened.getTextureRect().getSize() * 2; }
	void SetDoorDirection(int i);
	sf::Vector2f GetDoorDirection() const { return doorDirection; }
	bool GetDoorStart() const { return isStartKeyAnimation; }

	void PlayUnlock();
};
