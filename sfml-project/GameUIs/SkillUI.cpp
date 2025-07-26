#include "stdafx.h"
#include "SkillUI.h"

SkillUI::SkillUI(const std::string& name)
	: GameObject(name)
{
}

void SkillUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
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
}

void SkillUI::Release()
{
}

void SkillUI::Reset()
{
}

void SkillUI::Update(float dt)
{
}

void SkillUI::Draw(sf::RenderWindow& window)
{
}