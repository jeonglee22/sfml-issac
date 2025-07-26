#include "stdafx.h"
#include "HeartUI.h"

HeartUI::HeartUI(const std::string& textureId, const std::string& name)
	: texId(textureId), GameObject(name)
{
}

void HeartUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void HeartUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void HeartUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void HeartUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void HeartUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void HeartUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	texId = "";
}

void HeartUI::Release()
{
}

void HeartUI::Reset()
{

}

void HeartUI::Update(float dt)
{
}

void HeartUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}