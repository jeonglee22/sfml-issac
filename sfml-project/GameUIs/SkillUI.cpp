#include "stdafx.h"
#include "SkillUI.h"

SkillUI::SkillUI(const std::string& textureId, const std::string& name)
	: cooltimeImageId(textureId), GameObject(name)
{
}

void SkillUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
	if(skill != nullptr)
	{
		skill->SetPosition(pos);
		for (auto coolTimeImage : skillCooltimeImages)
			coolTimeImage->setPosition(pos + sf::Vector2f(50.f, 0.f));
	}
}

void SkillUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void SkillUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
	if (skill != nullptr)
	{
		skill->SetScale(s);
		for (auto coolTimeImage : skillCooltimeImages)
			coolTimeImage->setScale(s);
	}
}

void SkillUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void SkillUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void SkillUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	for (int i = 0; i < 3; i++)
	{
		skillCooltimeImages.push_back(new sf::Sprite());
	}
	skillCooltimeImageRect.push_back(sf::IntRect(4,1,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(20,1,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(36,1,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(52,1,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(4,33,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(20,33,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(36,33,8,30));
	skillCooltimeImageRect.push_back(sf::IntRect(52,33,8,30));
}

void SkillUI::Release()
{
}

void SkillUI::Reset()
{
	for (int i = 0; i < 2; i++)
	{
		skillCooltimeImages[i]->setTexture(TEXTURE_MGR.Get(cooltimeImageId), true);
		skillCooltimeImages[i]->setTextureRect(skillCooltimeImageRect[i]);
		skillCooltimeImages[i]->setOrigin((sf::Vector2f)skillCooltimeImageRect[i].getSize() * 0.5f);
	}
}

void SkillUI::Update(float dt)
{
	if (haveSkill)
	{
		skill->Reset();
		SetScale({ 2.5f,2.5f });
		SetSkillCoolTimeImage();

		haveSkill = false;
	}
}

void SkillUI::Draw(sf::RenderWindow& window)
{
	if (skill != nullptr)
	{
		skill->Draw(window);
		for (auto cooltimeImage : skillCooltimeImages)
		{
			window.draw(*cooltimeImage);
		}
	}
}

void SkillUI::SetSkillCoolTimeImage()
{
	CoolTime coolTime = (CoolTime)skill->GetTotalSkillCooltime();
	int rectPos = -1;
	switch (coolTime)
	{
	case SkillUI::CoolTime::twelve:
		rectPos = 2;
		break;
	case SkillUI::CoolTime::six:
		rectPos = 3;
		break;
	case SkillUI::CoolTime::four:
		rectPos = 4;
		break;
	case SkillUI::CoolTime::three:
		rectPos = 5;
		break;
	case SkillUI::CoolTime::two:
		rectPos = 6;
		break;
	case SkillUI::CoolTime::one:
		rectPos = 7;
		break;
	default:
		break;
	}
	skillCooltimeImages[2]->setTexture(TEXTURE_MGR.Get(cooltimeImageId), true);
	skillCooltimeImages[2]->setTextureRect(skillCooltimeImageRect[rectPos]);
	skillCooltimeImages[2]->setOrigin((sf::Vector2f)skillCooltimeImageRect[rectPos].getSize() * 0.5f);
}
