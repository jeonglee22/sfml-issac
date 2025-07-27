#pragma once
#include "Obstacles.h"

class Isaac;

class Spikes : public Obstacles
{
protected:
	Isaac* isaac;

	int damage = 1;

public:
	Spikes(const std::string& texId = "", const std::string& name = "");
	~Spikes() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	HitBox* GetHitBox() { return hitBox; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};

