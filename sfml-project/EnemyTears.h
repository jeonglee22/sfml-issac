#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class EnemyTears : public GameObject
{
protected:
    sf::Sprite sprite;
    Animator animator;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    float speed;
    int damage;
    float distance;
    float maxRange;
    bool isCrush = false;
    float crushTime = 0.0f;
    float crushMaxTime = 0.3f;
    HitBox hitBox;

public:
    EnemyTears(const std::string& name = "EnemyTears");

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

    void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d, float range = 200.0f);
    void Hit();
    void StartCrush();

    sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
    int GetDamage() const { return damage; }
    bool IsCrushed() const { return isCrush; }



};

