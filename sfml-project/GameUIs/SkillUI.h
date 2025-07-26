#pragma once
#include "GameObject.h"
#include "Skill.h"

class SkillUI :
    public GameObject
{
public:
	enum class CoolTime
	{
		one = 1,
		two,
		three,
		four,
		six = 6,
		twelve = 12,
	};

protected:
	sf::RectangleShape body;

	Skill* skill = nullptr;

	std::string cooltimeImageId;
	std::vector<sf::IntRect> skillCooltimeImageRect;
	std::vector<sf::Sprite*> skillCooltimeImages;

	int imageCoolTime = 0;
	bool haveSkill = false;
	float cooltimeBarLength = 24.f;
	float posOffset = 4.f;

public:
	SkillUI(const std::string& textureId = "", const std::string& name = "");
	virtual ~SkillUI() = default;

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

	void SetSkill(Skill* skill) 
	{ 
		this->skill = skill; 
		haveSkill = true; 
	}
	void SetSkillCoolTimeImage();
	void ChangeCoolTimeTexture();
};

