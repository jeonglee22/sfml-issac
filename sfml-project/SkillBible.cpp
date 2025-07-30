#include "stdafx.h"
#include "SkillBible.h"

void SkillBible::LoadJsonFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	file >> skillJson;

	file.close();
}

void SkillBible::ShowJsonRandomInfo()
{
	if (skillJson)
	{
		int length = skillJson.size();
		pickedId = Utils::RandomRange(0, skillCount);

		std::cout << pickedId << std::endl << skillJson[std::to_string(pickedId)] << std::endl;
	}
}

void SkillBible::AddTextureOfSkill()
{
	if (skillJson)
	{
		std::string fileName = "";
	}
}
