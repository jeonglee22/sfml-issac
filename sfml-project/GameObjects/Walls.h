#pragma once
#include "SpriteGo.h"
class HitBox;

class Walls : public SpriteGo
{
protected:
	HitBox* hitBox;

public:
	Walls(const std::string& texId = "", const std::string& name = "");
	virtual ~Walls() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	HitBox* GetHitBox() { return hitBox; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};

