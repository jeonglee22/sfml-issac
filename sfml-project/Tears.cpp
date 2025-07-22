#include "stdafx.h"
#include "Tears.h"

Tears::Tears(const std::string& name)
	: GameObject(name)
{
}

void Tears::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Tears::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Tears::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Tears::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Tears::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Tears::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Tears::Release()
{
}

void Tears::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(texture));
	Utils::SetOrigin(sprite, Origins::MC);
	SetPosition({ 10.f,10.f });
	SetScale({ 2.f, 2.f });
}

void Tears::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
}

void Tears::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Tears::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;
}


