#pragma once
#include "Isaac.h"
#include "Skill.h"
#include "SceneGame.h"
#include "Monster.h"
#include "SkillFunctions.h"

class Skill;

class SkillFunctionBible
{
protected:
	Isaac* isaac = nullptr;

	std::unordered_map<std::string, Skill*> skillFunctionBible;
	std::vector<std::string> skillNames;

public:
	SkillFunctionBible() = default;
	~SkillFunctionBible() = default;

	void SetIsaac();
	void AddSkillFunction();
	Skill* GetSkill(const std::string& str) { return skillFunctionBible[str]; }
	std::vector<std::string> GetSkillNames() const { return skillNames; }
};


