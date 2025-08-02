#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"
#include "Map.h"

class Bomb : public GameObject
{
protected:
	sf::Sprite bomb;
    sf::Sprite bombRadius;
	Animator animator;
    Animator radiusAnimator;
	HitBox hitBox;

	float explosionTime = 0.0f;
	float explosionMaxTime = 5.0f;

    float explosionAnimationTime = 0.0f;
    float explosionAnimationMaxTime = 0.5f;

    float explosionDistance = 80.f;

    bool wasExplosion = false;

public:
    Bomb(const std::string& name = "");
    virtual ~Bomb() = default;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(Origins preset) override;
    void SetOrigin(const sf::Vector2f& o) override;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void Explosion();

    void SetHiddenNeighboorDoorOpen(Map* hiddenMap, sf::Vector2f doorDir);
};

