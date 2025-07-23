#include "stdafx.h"
#include "Monster.h"
#include "MonsterState.h"

Monster::Monster(const std::string& name, Monsters type)
	: GameObject(name), monsterType(type)
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

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Monster::Release()
{
}

void Monster::Update(float dt)
{
	if (currentState)
	{
		currentState->Update(this, dt);
	}

	UpdateSkillTimer(dt);
	animator.Update(dt);

	position += velocity * dt;
	SetPosition(position);
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Monster::ChangeState(MonsterState* newState)
{
	if (currentState)
	{
		currentState->Exit(this);
	}
	currentState = newState;
	if (currentState)
	{
		currentState->Enter(this);
	}
}

std::string Monster::GetCurrentStateName() const
{
	return currentState ? currentState->GetStateName() : "None";
}

void Monster::TakeDamage(int damage)
{
	currentHP -= damage;
	if (currentHP < 0)
	{
		currentHP = 0;
	}
}

float Monster::GetDistanceToPlayer() const
{
	sf::Vector2f diff = playerPosition - position;
	return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

void Monster::UpdateSkillTimer(float dt)
{
	if (skillTimer > 0)
	{
		skillTimer -= dt;
		if (skillTimer <= 0)
		{
			canUseSkill = true;
		}
	}
}
