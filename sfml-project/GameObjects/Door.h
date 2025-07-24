#pragma once
#include "SpriteGo.h"
#include "HitBox.h"

class Door : public SpriteGo
{
protected:
	sf::Sprite doorClosedLeft;
	sf::Sprite doorClosedRight;
	sf::Sprite doorOpened;

	HitBox hitBox;

	bool isCleared = false;

	sf::Vector2f doorOffset = { 0.f,0.f };

public:
	Door(const std::string& texId = "", const std::string& name = "");
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

	HitBox GetHitBox() const { return hitBox; }
	sf::Vector2i GetDoorSize() const { return doorOpened.getTextureRect().getSize(); }
};
