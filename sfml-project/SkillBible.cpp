#include "stdafx.h"
#include "SkillBible.h"

void SkillBible::LoadJsonFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	file >> skillJson;

	file.close();
}
