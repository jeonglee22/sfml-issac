#pragma once
#include "Animator.h"
#include "HitBox.h"

class HitBox;
class Tears;
class SceneDev2;
class SceneGame;

class Isaac : public GameObject
{
protected:
	sf::Sprite body;
	sf::Sprite head;
	Animator bodyAnimator;
	Animator headAnimator;

	std::list<Tears*> tearsList;
	std::list<Tears*> tearsPool;
	SceneDev2* sceneDev2 = nullptr;
	SceneGame* sceneGame = nullptr;

	sf::Vector2f velocity = { 0.f, 0.f };
	float speed = 350.f;

	float shootTimer = 0.0f;
	float shootInterval = 0.4f;
	sf::Vector2f shootDirection = { 0.f, 0.f };
	bool wasKeyPressed = false;

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

	void FireTear(const sf::Vector2f& direction);
};
