#pragma once
#include <json/json.h>
#include <Skill.h>

class SkillBible
{
protected:
	std::vector<Skill*> skills;

	Json::Value skillJson;

public:
	SkillBible() = default;
	~SkillBible() = default;

	void LoadJsonFile(const std::string& filePath);

};

