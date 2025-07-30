#pragma once
#include <json/json.h>
#include <Skill.h>

class SkillBible
{
protected:
	std::vector<Skill*> skills;
	std::vector<std::function<void()>> skillFunctions;

	Json::Value skillJson;

	Skill* pickedSkill;

	int skillCount = 300;

	int pickedId = -1;

public:
	SkillBible() = default;
	~SkillBible() = default;

	void LoadJsonFile(const std::string& filePath);

	void PickJsonRandomInfo();

	void PickSkill();

	Skill* GetSkill() { return pickedSkill; }

	std::string ConvertName(const std::string& str);
};

