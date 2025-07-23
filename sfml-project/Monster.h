#pragma once
#include "GameObject.h"
#include "Animator.h"


class Monster : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	Monsters monsterType;

	int currentHP = 0;
	int maxHP = 0;

	float speed = 0.0f;




public:
	Monster(const std::string& name, Monsters monsters);
	virtual ~Monster() = default;

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

