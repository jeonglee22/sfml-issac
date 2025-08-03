#pragma once
#include "GameObject.h"
class PauseUI : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/pausescreen.png";
	sf::IntRect bodyRect= { 0, 0, 237, 206 };

	sf::RectangleShape blackBack;

	sf::Sprite pointer;
	sf::IntRect pointerRect = { 243, 4, 11, 9 };
	std::vector<sf::Vector2f> pointerPos =
	{
		{340.f,370.f},
		{370.f,410.f}
	};
	int pos = 0;

	bool isRestart = false;

public:
	PauseUI(const std::string& textureId = "", const std::string& name = "");
	virtual ~PauseUI() = default;

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

	bool GetIsRestart() const { return isRestart; }
	void SetIsRestart(bool b) { isRestart = b; }
};

