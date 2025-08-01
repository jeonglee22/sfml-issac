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

struct Boom
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_019_boom.png", "boom");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					for(int i = 0; i < 10; i++)
						isaac->AddItem(Items::Bomb);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct Lunch
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_022_lunch.png", "lunch");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetMaxHP(isaac->GetMaxHP() + 2);
					isaac->SetCurrentHP(isaac->GetCurrentHP() + 2);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct Dinner
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_023_dinner.png", "dinner");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetMaxHP(isaac->GetMaxHP() + 2);
					isaac->SetCurrentHP(isaac->GetCurrentHP() + 2);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct Dessert
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_024_dessert.png", "dessert");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetMaxHP(isaac->GetMaxHP() + 2);
					isaac->SetCurrentHP(isaac->GetCurrentHP() + 2);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct Breakfast
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_025_breakfast.png", "breakfast");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetMaxHP(isaac->GetMaxHP() + 2);
					isaac->SetCurrentHP(isaac->GetCurrentHP() + 2);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};

struct TammyHead
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_038_tammyshead.png", "tammyshead");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					std::vector<Tears*> tears;
					for (int i = 0; i < 10; i++)
					{
						Tears* tear = new Tears();
						tear->Init();
						tear->Reset();
						sceneGame->AddGameObject(tear);
						sf::Vector2f tearDirection = Utils::GetNormal({ std::cos(Utils::DegreeToRadian(36 * i)), std::sin(Utils::DegreeToRadian(36 * i)) });
						tear->Fire(isaac->GetPosition() - sf::Vector2f(0.f, 20.f), tearDirection, isaac->GetTearSpeed(), isaac->GetTearDamage() + 250.f);
					}
				}
			});
		skill->SetTotalSkillCooltime(1);

		return skill;
	};
};

struct YumHeart
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_045_yumheart.png", "yumheart");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetCurrentHP(Utils::Clamp(isaac->GetCurrentHP() + 2, 0, isaac->GetMaxHP()));
				}
			});
		skill->SetTotalSkillCooltime(4);

		return skill;
	};
};

struct MomsEye
{
	Skill* operator() ()
	{
		Skill* skill = new Skill("graphics/additionals/collectibles/collectibles_055_momseye.png", "momseye");

		skill->SetSkillFunc([]()
			{
				if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				{
					SceneGame* sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
					Isaac* isaac = sceneGame->GetIsaac();
					isaac->SetBackShoot(true);
				}
			});
		skill->SetSkillPassive(true);

		return skill;
	};
};