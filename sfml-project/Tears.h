#pragma once
#include "GameObject.h"
class Tears : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string texture = "graphics/only_tears.png";

	sf::Vector2f direction;
	float speed = 0.f;
	int damage = 0;


public:
	Tears(const std::string& name = "");
	virtual ~Tears() = default;

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

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d);

};

