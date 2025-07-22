#pragma once
#include "Animator.h"
#include "HitBox.h"

class HitBox;

class Isaac : public GameObject
{
protected:
	sf::Sprite body;
	sf::Sprite head;
	Animator bodyAnimator;
	Animator headAnimator;

	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
	float speed = 400.f;

	HitBox hitBox;

public:
	Isaac(const std::string& name = "");
	~Isaac() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
