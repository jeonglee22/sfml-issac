#pragma once

#include "Isaac.h"

class SkillFunctionBible
{
protected:
	Isaac* isaac = nullptr;

	std::unordered_map<std::string, std::function<void()>> skillFunctionBible;

public:
	SkillFunctionBible() = default;
	~SkillFunctionBible() = default;

	void SetIsaac();
	void AddSkillFunction(const std::string& skillName, std::function<void()>& func);
};

