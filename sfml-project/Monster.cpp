#include "stdafx.h"
#include "Monster.h"

Monster::Monster(const std::string& name, Monsters monsters)
	: GameObject(name), monsterType(monsters)
{
}

void Monster::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Monster::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Monster::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Monster::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Monster::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Monster::Init()
{
	animator.SetTarget(&body);
}

void Monster::Release()
{
}

void Monster::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	if (monsterType == Monsters::fly)
	{
		animator.Play("animations/fly.csv");
	}



	SetScale({ 2.0f, 2.0f });
	SetOrigin(Origins::BC);
}

void Monster::Update(float dt)
{
	animator.Update(dt);
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}