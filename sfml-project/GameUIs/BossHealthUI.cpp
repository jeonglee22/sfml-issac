#include "stdafx.h"
#include "BossHealthUI.h"

BossHealthUI::BossHealthUI(const std::string& name)
	: GameObject(name)
{
}

void BossHealthUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void BossHealthUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void BossHealthUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void BossHealthUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void BossHealthUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void BossHealthUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 10;
}

void BossHealthUI::Release()
{
}

void BossHealthUI::Reset()
{
	barRemain.setTexture(TEXTURE_MGR.Get(barId));
	barRemain.setTextureRect(barRect[0]);
	barRemain.setOrigin((sf::Vector2f)barRect[0].getSize() * 0.5f);
	barRemain.setScale({ 2.f,2.f });
	barRemain.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 50.f });

	barBackground.setTexture(TEXTURE_MGR.Get(barId));
	barBackground.setTextureRect(barRect[1]);
	barBackground.setOrigin((sf::Vector2f)barRect[1].getSize() * 0.5f);
	barBackground.setScale({ 2.f,2.f });
	barBackground.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 50.f });

	SetActive(false);
}

void BossHealthUI::Update(float dt)
{
	sf::IntRect newRemainRect, newHurtRect;
	newRemainRect = barRect[0];
	newRemainRect.width = barPos;
	newHurtRect = barRect[1];
	newHurtRect.left = barRect[1].left + barPos;
	newHurtRect.width = 131 - barPos;
	std::cout << barPos << std::endl;
	barRemain.setTextureRect(newRemainRect);
	barBackground.setTextureRect(newHurtRect);
	sf::Vector2f newOrigin = barBackground.getOrigin();
	newOrigin.x = barRect[1].getSize().x * -0.5f + newHurtRect.width;
	barBackground.setOrigin(newOrigin);
}

void BossHealthUI::Draw(sf::RenderWindow& window)
{
	window.draw(barBackground);
	window.draw(barRemain);
}