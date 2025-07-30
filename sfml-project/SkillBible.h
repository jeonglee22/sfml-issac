#pragma once
#include <json/json.h>
#include <Skill.h>

class SkillBible
{
protected:
	std::vector<Skill*> skills;
	std::vector<std::function<void()>> skillFunctions;

	Json::Value skillJson;

	sf::Sprite* skill;

	int skillCount = 340;

	int pickedId = -1;

public:
	SkillBible() = default;
	~SkillBible() = default;

	void LoadJsonFile(const std::string& filePath);

	void ShowJsonRandomInfo();

	void AddTextureOfSkill();
};

