#pragma once
#include "SpriteGo.h"

class HitBox;

class Obstacles : public SpriteGo
{
protected:
	HitBox* hitBox;

public:
	Obstacles(const std::string& texId = "", const std::string & name = "");
	virtual ~Obstacles() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	HitBox* GetHitBox() { return hitBox; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};

