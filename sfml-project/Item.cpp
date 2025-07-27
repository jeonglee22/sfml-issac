#include "stdafx.h"
#include "Item.h"

Item::Item(const std::string& name)
	: GameObject(name)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Item::Init()
{
	animator.SetTarget(&sprite);
}

void Item::Release()
{
}

void Item::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;


	switch (itemType)
	{
	case Items::Coin:
		animator.Play("animations/coin.csv");
		break;
	case Items::Heart:
		animator.Play("animations/heart.csv");
		break;
	case Items::Half_Heart:
		animator.Play("animations/half_heart.csv");
		break;
	case Items::Bomb:
		animator.Play("animations/bomb.csv");
		break;
	case Items::Key:
		animator.Play("animations/key.csv");
		break;
	}

	SetScale({ 2.f, 2.f });
	SetOrigin(Origins::BC);
}

void Item::Update(float dt)
{
	animator.Update(dt);

	if(itemType == Items::Heart || itemType == Items::Half_Heart)
	{
		beatTime += dt;

		if (beatTime > 0.2f)
		{
			if (isLarge)
			{
				SetScale({ 2.0f, 2.0f });
				isLarge = false;
			}
			else
			{
				SetScale({ 2.0f, 1.6f });
				isLarge = true;
			}
			beatTime = 0.0f;
		}
	}

	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	hitBox.Draw(window);
}