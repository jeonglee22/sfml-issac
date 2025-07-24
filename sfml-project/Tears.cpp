#include "stdafx.h"
#include "Tears.h"
#include "SceneGame.h"
#include "Monster.h"
#include "Animator.h"

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
	animator.SetTarget(&sprite);

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Tears::Release()
{
}

void Tears::Reset()
{
	animator.Play("animations/tears_idle.csv");

	tearsCrushTime = 0.0f;
	isTearsCrush = false;
	damage = 35;

	Utils::SetOrigin(sprite, Origins::MC);
	SetScale({ 1.5f, 1.5f });
}

void Tears::Update(float dt)
{
	if (isTearsCrush)
	{
		animator.Update(dt);
		tearsCrushTime += dt;

		if (tearsCrushTime >= tearsCrushMaxTime)
		{
			SetActive(false);
		}
		return;
	}

	animator.Update(dt);

	sf::Vector2f moveVector = velocity * dt;
	distance += Utils::Magnitude(moveVector);

	if (distance > maxRange && abs(direction.y) < 0.5f)
	{
		velocity += gravity * dt;
	}

	SetPosition(position + velocity * dt);

	if (direction.y <= 0.f && position.y > startPosition.y + 30.f)
	{
		StartSplash();
		SetOrigin(Origins::MC);
		return;
	}
	if (position.y > 500.f || position.y < -500.f)
	{
		SetActive(false);
	}

	Hit();

	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());
}

void Tears::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	hitBox.Draw(window);
}

void Tears::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SetPosition(pos);
	startPosition = pos;
	direction = dir;
	velocity = dir * s;
	speed = s;
	damage = d;
	distance = 0.f;
}

void Tears::Hit()
{
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	auto monsters = scene->GetMonsters();

	sf::FloatRect isaacBounds = sprite.getGlobalBounds();

	for (auto& monster : monsters)
	{
		if (!monster->GetActive() || monster->IsDead())
		{
			continue;
		}

		sf::FloatRect monsterBounds = monster->GetHitBoxMonster();

		if (isaacBounds.intersects(monsterBounds))
		{
			monster->TakeDamage(damage);
			
			StartSplash();
			SetOrigin(Origins::MC);
			isTearsCrush = true;
			return;
		}

	}

}

void Tears::StartSplash()
{
	if (isTearsCrush) return;

	animator.Play("animations/tears_boom.csv");

	isTearsCrush = true;
	tearsCrushTime = 0.0f;
	damage = 0;

	velocity = { 0.f, 0.f };
}


