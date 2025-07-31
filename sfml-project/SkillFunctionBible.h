#pragma once
#include "Isaac.h"
#include "Skill.h"
#include "SceneGame.h"
#include "Monster.h"

class Skill;

class SkillFunctionBible
{
protected:
	Isaac* isaac = nullptr;

	std::unordered_map<std::string, Skill*> skillFunctionBible;

public:
	SkillFunctionBible() = default;
	~SkillFunctionBible() = default;

	void SetIsaac();
	void AddSkillFunction();
	Skill* GetSkill(const std::string& str) { return skillFunctionBible[str]; }
};

struct Necronomicon
{
	Skill* operator() () 
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_035_thenecronomicon.png", "necronomicon");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame *) SCENE_MGR.GetCurrentScene();
					for (auto monster : sceneGame->GetMonsters())
					{
						if (!monster->GetActive() || monster->IsDead())
						{
							continue;
						}
						monster->TakeDamage(400);
					}
				}
			});
		skill->SetTotalSkillCooltime(4);
		skill->SetEffectId("graphics/giantbook_001_necronomicon.png");
		skill->SetEffectBody();
		sf::Sprite& body = skill->GetEffectBody();
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
		{
			SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
			body.setOrigin(sf::Vector2f( body.getTexture()->getSize().x * 0.5f , body.getTexture()->getSize().y));
			body.setPosition(sceneGame->GetWorldView().getCenter());
			body.setScale({ 2.f,2.f });
		}
		return skill;
	};
};
