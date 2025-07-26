#pragma once
#include "GameObject.h"
class ItemUI :public GameObject
{
protected:
	sf::RectangleShape body;

	std::vector<std::string> fontImage;
	sf::Vector2f fontImageSize = { 9.f,11.f };

	sf::Sprite coinImage;
	sf::IntRect coinRect = {4,3,9,11};
	std::vector<sf::Sprite*> coinCountSprites;
	std::vector<sf::Vector2f> coinImagesPos;

	sf::Sprite bombImage;
	sf::IntRect bombRect = { 1,17,13,13 };
	std::vector<sf::Sprite*> bombCountSprites;
	std::vector<sf::Vector2f> bombImagesPos;

	sf::Sprite keyImage;
	sf::IntRect keyRect = { 20,2,9,12 };
	std::vector<sf::Sprite*> keyCountSprites;
	std::vector<sf::Vector2f> keyImagesPos;

	int coinCount = 5;
	int bombCount = 0;
	int keyCount = 0;

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

	void SetCoinCount(int count);
	int GetCoinCount() { return coinCount; }
	void SetBombCount(int count);
	int GetBombCount() { return bombCount; }
	void SetKeyCount(int count);
	int GetKeyCount() { return keyCount; }
};

