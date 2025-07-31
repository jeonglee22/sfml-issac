#pragma once
#include "stdafx.h"
#include "Isaac.h"
#include "Skill.h"
#include "SceneGame.h"
#include "Monster.h"
#include "Tears.h"

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
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_002_theinnereye.png", "theinnereye");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetTearCount(3);
					isaac->SetShootInterval(isaac->GetShootInterval() * 2.1f);
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

struct NumberOne
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_006_numberone.png", "numberone");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetShootInterval(isaac->GetShootInterval() / 1.5f);
					Tears::AddTearRange(-100.f);
					Tears::SetTearColor(sf::Color::Yellow);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct BloodMartyr
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_007_bloodofthemartyr.png", "bloodofthemartyr");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetTearDamage(isaac->GetTearDamage() + 10.f);
					Tears::SetTearColor(sf::Color::Red);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};
