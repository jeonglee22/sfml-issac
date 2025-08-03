#pragma once
#include "GameObject.h"
class BossHealthUI : public GameObject
{
protected:
	sf::Sprite body;
	std::string barId = "graphics/ui_bosshealthbar.png";

	sf::Sprite barRemain;
	sf::Sprite barBackground;

	std::vector<sf::IntRect> barRect = {
		{3,5,131,20},
		{3,37,131,20},
	};

	int barPos = 131;

public:
	BossHealthUI(const std::string& name = "");
	virtual ~BossHealthUI() = default;

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

	void SetBarPos(int p) { barPos = p; }
};

