#include "stdafx.h"
#include "ItemAltar.h"
#include "SkillBible.h"
#include "Skill.h"
#include "SkillUI.h"
#include "Isaac.h"
#include "SceneGame.h"

ItemAltar::ItemAltar(const std::string& texId, const std::string& name)
	:Obstacles(texId, name)
{
}

void ItemAltar::SetPosition(const sf::Vector2f& pos)
{
	SpriteGo::SetPosition(pos);
	skill->SetPosition(pos + skillPos);
}

void ItemAltar::SetRotation(float rot)
{
	SpriteGo::SetRotation(rot);
	skill->SetRotation(rot);
}

void ItemAltar::SetScale(const sf::Vector2f& s)
{
	SpriteGo::SetScale(s);
	skill->SetScale(s);
}

void ItemAltar::SetOrigin(const sf::Vector2f& o)
{
	SpriteGo::SetOrigin(o);
	skill->SetOrigin(o);
}

void ItemAltar::SetOrigin(Origins preset)
{
	SpriteGo::SetOrigin(preset);
}

void ItemAltar::Init()
{
	bible = new SkillBible();
	bible->LoadJsonFile("graphics/items/items.json");
	
	Obstacles::Init();
}

void ItemAltar::Release()
{
}

void ItemAltar::Reset()
{
	Obstacles::Reset();

	bible->PickJsonRandomInfo();
	bible->PickSkill();

	skill = bible->GetSkill();
	skill->sortingLayer = SortingLayers::Foreground;
	skill->sortingOrder = 1;
	skill->Reset();
	skill->SetOrigin(Origins::TL);
	skill->SetPosition(this->GetPosition() + skillPos);
	skill->SetScale({ 2.f,2.f });

	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
	{
		isaac = ((SceneGame*)SCENE_MGR.GetCurrentScene())->GetIsaac();
		skillUI = ((SceneGame*)SCENE_MGR.GetCurrentScene())->GetSkillUI();
	}
}

void ItemAltar::Update(float dt)
{
	Obstacles::Update(dt);

	if(skill != nullptr && skill->GetActive())
	{
		skill->SetPosition(skill->GetPosition() + sf::Vector2f(0, dir) * dt * 5.f);
		movingTime += dt;
		if (movingTime > movingTimeMax)
		{
			dir *= -1.f;
			movingTime = 0.f;
		}
		changeCoolTime += dt;
	}

	if (Utils::CheckCollision(isaac->GetHitBoxBody().rect, hitBox->rect) && IsGetSkill && changeCoolTime > changeCoolTimeMax)
	{
		if (!skill->GetSkillPassive())
		{
			Skill* temp = nullptr;
			if (isaac->GetActiveSkill() != nullptr)
			{
				temp = isaac->GetActiveSkill();
			}
			isaac->SetActiveSkill(skill);
			skillUI->SetSkill(skill);
			skill = temp;
		}
		else
		{
			isaac->SetPassiveSkill(skill);
			skill->ApplyPassive();
		}

		if (skill != nullptr && skill->GetSkillPassive())
		{
			skill->SetActive(false);
		}

		IsGetSkill = false;
		if (skill != nullptr && !skill->GetSkillPassive())
		{
			IsGetSkill = true;
			skill->sortingLayer = SortingLayers::Foreground;
			skill->sortingOrder = 1;
			skill->Reset();
			skill->SetOrigin(Origins::TL);
			skill->SetPosition(this->GetPosition() + skillPos);
			skill->SetScale({ 2.f,2.f });
			movingTime = 0.f;
		}
		changeCoolTime = 0.f;
	}
}

void ItemAltar::Draw(sf::RenderWindow& window)
{ 
	Obstacles::Draw(window);

	if (skill != nullptr && skill->GetActive())
	{
		skill->Draw(window);
	}
}
