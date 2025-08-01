#pragma once
#include "Obstacles.h"

class Isaac;
class Skill;
class SkillUI;
class SkillBible;

class ItemAltar : public Obstacles
{
protected:
	Isaac* isaac = nullptr;

	Skill* skill = nullptr;
	SkillUI* skillUI = nullptr;
	SkillBible* bible = nullptr;
	
	float getSkillTime = 0.0f;
	float getSkillMaxTime = 1.0f;

	sf::Vector2f skillPos = sf::Vector2f(-5.f, -50.f);

	float movingTimeMax = 1.f;
	float movingTime = 0.f;
	float dir = -1.f;

	float changeCoolTime = 0.f;
	float changeCoolTimeMax = 1.f;

	bool IsGetSkill = true;

public:
	ItemAltar(const std::string& texId = "", const std::string& name = "");
	~ItemAltar() override = default;

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

	HitBox* GetHitBox() { return hitBox; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};

