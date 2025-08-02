#include "stdafx.h"
#include "Skill.h"
#include "SpriteGo.h"

Skill::Skill(const std::string& textureId, const std::string& name)
	: texId(textureId), GameObject(name)
{
}

void Skill::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Skill::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Skill::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Skill::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Skill::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Skill::Init()
{
}

void Skill::Release()
{
}

void Skill::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId),true);
	SetOrigin(Origins::MC);
}

void Skill::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Q) && skillCoolTime == currentCoolTime && !isPassive)
	{
		isUseSkill = true;
		skillFunc();
		currentCoolTime = 0;
		//effectBody->SetActive(true);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		AddSkillCooltime();
	}

	if (isUseSkill)
	{
		skillActionTime += dt;
		if (skillActionTime > skillActionMax)
		{
			skillActionTime = 0.f;
			isUseSkill = false;
			//effectBody->SetActive(false);
		}
	}
}

void Skill::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	if(isUseSkill && effectBody)
	{
		effectBody->Draw(window);
	}
}

void Skill::SetEffectBody()
{
	TEXTURE_MGR.Load(effectId);
	effectBody = new SpriteGo(effectId);
	effectBody->Reset();
}
