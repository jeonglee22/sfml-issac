#pragma once
#include "GameObject.h"
class ItemUI :public GameObject
{
protected:
	sf::RectangleShape body;

public:
	ItemUI(const std::string& name = "");
	virtual ~ItemUI() = default;

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
};

