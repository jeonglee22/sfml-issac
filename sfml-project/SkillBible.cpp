#include "stdafx.h"
#include "SkillBible.h"

void SkillBible::LoadJsonFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	file >> skillJson;

	file.close();
}

void SkillBible::PickJsonRandomInfo()
{
	if (skillJson)
	{
		pickedId = Utils::RandomRange(1, skillCount);
	}
}

void SkillBible::PickSkill()
{
	if (skillJson)
	{
		auto status = skillJson[std::to_string(pickedId)];

		while (status == Json::nullValue)
		{
			std::cout << pickedId << std::endl;
			PickJsonRandomInfo();
			status = skillJson[std::to_string(pickedId)];
		}

		std::vector<std::string> memberNames;
		for (int i = 0; i < status.size(); i++)
		{
			memberNames.push_back(status.getMemberNames()[i]);
		}

		std::string name;
		if (std::find(memberNames.begin(), memberNames.end(), "name") != memberNames.end())
			name = status["name"].asString();
		std::cout << name << ", " << pickedId << std::endl;

		std::string texId = "graphics/additionals/collectibles/collectibles_";
		if (pickedId < 10)
		{
			texId += "00" + std::to_string(pickedId) + "_";
		}
		else if (pickedId < 100)
		{
			texId += "0" + std::to_string(pickedId) + "_";
		}
		else
		{
			texId += std::to_string(pickedId) + "_";
		}
		std::string convertedName = ConvertName(name);
		texId += convertedName + ".png";

		pickedSkill = new Skill(texId, convertedName);
		TEXTURE_MGR.Load(texId);
	}
}

std::string SkillBible::ConvertName(const std::string& str)
{
	std::string result;

	for (const char& c : str)
	{
		if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
			result += c;
		else if (c >= 'A' && c <= 'Z')
			result += c - ('A' - 'a');
		else
			continue;
	}

	return result;
}
