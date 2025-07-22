#pragma once
#include "GameObject.h"
class MapBoxUI :
    public GameObject
{
protected:
	sf::RectangleShape body;
	std::vector<sf::RectangleShape> grid;

	int gridXcount = 10;
	int gridYcount = 16;
	sf::Vector2f gridSize = { 60.f,60.f };

	std::vector<sf::IntRect> gridRect;

public:
	MapBoxUI(const std::string& name = "");
	virtual ~MapBoxUI() = default;

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

	void SetGridRectValue();
	sf::Vector2f GetRectCenterHavePoint(const sf::Vector2f& point);
	sf::Vector2f GetGridSize() { return gridSize; }

};

