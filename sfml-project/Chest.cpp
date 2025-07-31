#include "stdafx.h"
#include "Chest.h"

Chest::Chest(const std::string& name)
	: GameObject(name)
{
}

void Chest::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Chest::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Chest::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Chest::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Chest::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Chest::Init()
{
	animator.SetTarget(&sprite);

}

void Chest::Release()
{
}

void Chest::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	animator.Play("animations/chest_normal.csv");
	SetScale({ 2.0f,2.0f });
}

void Chest::Update(float dt)
{
	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());
}

void Chest::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	hitBox.Draw(window);
}

void Chest::ChestOpen()
{
	animator.Play("animations/chest_normal_open.csv");
	isOpen = true;
}