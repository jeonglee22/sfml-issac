#pragma once
#include "GameObject.h"

class HeartUI : public GameObject
{
protected:
	sf::RectangleShape body;

	std::string texId;
	
	std::vector<sf::Sprite*> hearts;

public:
	HeartUI(const std::string& textureId = "", const std::string & name = "");
	virtual ~HeartUI() = default;

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

