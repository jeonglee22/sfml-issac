#include "stdafx.h"
#include "ItemUI.h"

ItemUI::ItemUI(const std::string& name)
	: GameObject(name)
{
}

void ItemUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void ItemUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void ItemUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void ItemUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void ItemUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void ItemUI::Init()
{
}

void ItemUI::Release()
{
}

void ItemUI::Reset()
{
}

void ItemUI::Update(float dt)
{
}

void ItemUI::Draw(sf::RenderWindow& window)
{
}