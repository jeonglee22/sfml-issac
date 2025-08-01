#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "Animator.h"

class Monster;
class SceneGame;

class Tears : public GameObject
{
protected:
	sf::Sprite sprite;
	Animator animator;

	sf::Vector2f direction;
	sf::Vector2f velocity;
	float speed = 0.f;
	int damage = 35;
	int initDamage = 35;

	float distance = 0.f;
	
	sf::Vector2f startPosition;
	sf::Vector2f gravity = { 0.f, 800.f };

	float tearsCrushTime = 0.0f;
	float tearsCrushMaxTime = 1.0f;
	bool isTearsCrush = false;

	sf::Vector2f maxRangePosition;
	bool hasReachedMaxRange = false;

	SceneGame* sceneGame;
	HitBox hitBox;

	static float maxRange;
	static std::string tearIdle;
	static std::string tearBoom;
	static sf::Color tearColor;

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
	void Hit();
	void StartSplash();

	static void SetTearIdleAni(const std::string& idleAni) { Tears::tearIdle = idleAni; }
	static void SetTearBoomAni(const std::string& boomAni) { Tears::tearBoom = boomAni; }
	static void SetTearColor(const sf::Color& c) { Tears::tearColor = c; }
	static void AddTearRange(float t) { Tears::maxRange = Utils::Clamp(Tears::maxRange + t, 50.f, 1000.f); }
};

