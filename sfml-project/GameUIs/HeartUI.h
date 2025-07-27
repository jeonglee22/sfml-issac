#pragma once
#include "GameObject.h"

class HeartUI : public GameObject
{
protected:
	sf::RectangleShape body;

	std::string texId;
	
	std::vector<sf::Sprite*> hearts;

	sf::Vector2f seperatePos = { 13.f, 0.f };

	sf::IntRect fullHeart = { 1,1,15,14 };
	sf::IntRect halfHeart = { 17,1,15,14 };
	sf::IntRect emptyHeart = { 33,1,15,14 };

	int maxHPCount = 6;
	int beforeMaxHPCount = 6;
	int currentHPCount = 6;
	int beforeHPCount = 6;

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

	void SetHeartCount(int hp) { currentHPCount = hp; }
	int GetHeartCount() const { return currentHPCount; }
	void SetMaxHeartCount(int hp) { maxHPCount = hp; }
	int GetMaxHeartCount() const { return maxHPCount; }
};

