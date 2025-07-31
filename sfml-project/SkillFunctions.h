#pragma once
#include "stdafx.h"
#include "Isaac.h"
#include "Skill.h"
#include "SceneGame.h"
#include "Monster.h"

class Skill;

struct Necronomicon
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_035_thenecronomicon.png", "necronomicon");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
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
			body.setOrigin(sf::Vector2f(body.getTexture()->getSize().x * 0.5f, body.getTexture()->getSize().y));
			body.setPosition(sceneGame->GetWorldView().getCenter());
			body.setScale({ 2.f,2.f });
		}
		return skill;
	};
};

struct TheSadOnion
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_001_thesadonion.png", "sadonion");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetShootInterval(isaac->GetShootInterval() * 0.7f);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct TheInnerEye
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_002_theinnereye.png", "sadonion");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetTearCount(3);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct CricketsHead
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_004_cricketshead.png", "cricketshead");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetTearDamage((isaac->GetTearDamage() + 5) * 1.5f);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};