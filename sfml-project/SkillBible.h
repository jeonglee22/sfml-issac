#pragma once
#include <json/json.h>
#include <Skill.h>

class SkillFunctionBible;

class SkillBible
{
protected:
	Json::Value skillJson;

	Skill* pickedSkill = nullptr;
	SkillFunctionBible* bible;

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

