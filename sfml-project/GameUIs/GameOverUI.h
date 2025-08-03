#pragma once
#include "GameObject.h"
class GameOverUI : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/death portraits.png";
	sf::IntRect bodyRect = { 200, 0, 216, 256 };

	sf::RectangleShape blackBack;
	
	sf::Sprite exitWidget;
	sf::Sprite exitText;
	sf::Sprite restartWidget;
	sf::Sprite restartText;
	std::string widgetId = "graphics/backselectwidget.png";
	std::string exitId = "graphics/esc.png";
	std::string restartId = "graphics/space.png";

	std::vector<sf::IntRect> widgetRect =
	{
		{8,132,87,78},
		{99, 132, 108,113}
	};

	bool isRestart = false;

public:
	GameOverUI(const std::string& name = "");
	virtual ~GameOverUI() = default;

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

