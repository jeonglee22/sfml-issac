#pragma once
#include "GameObject.h"

class Skill : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId;

	sf::Sprite effectBody;
	std::string effectId;

	int skillCoolTime = 0;
	int currentCoolTime = 0;

	std::function<void()> skillFunc;

	bool isUseSkill = false;
	float skillActionMax = 1.f;
	float skillActionTime = 0.f;

	bool isPassive = false;

public:
	Skill(const std::string& textureId = "", const std::string& name = "");
	virtual ~Skill() = default;

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

	void SetTotalSkillCooltime(int c) { skillCoolTime = c; currentCoolTime = c; }
	int GetTotalSkillCooltime() const { return skillCoolTime; }
	void SetEffectId(const std::string& str) { effectId = str; }
	std::string GetEffectId() const { return effectId; }
	void SetEffectBody();
	sf::Sprite& GetEffectBody() { return effectBody; }
	int GetCurrentCooltime() const { return currentCoolTime; }
	void AddSkillCooltime() { currentCoolTime = Utils::Clamp(++currentCoolTime, 0, skillCoolTime); }
	void SetSkillFunc(const std::function<void()>& func) { skillFunc = func; }
	void SetSkillPassive(bool b) { isPassive = b; }
	bool GetSkillPassive() { return isPassive; }
	std::string GetTextId() const { return texId; };

	void ApplyPassive() { skillFunc(); }
};

