#include "stdafx.h"
#include "Monster.h"
#include "MonsterState.h"
#include "Obstacles.h"
#include "SceneGame.h"

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
	if (isDead)
	{
		animator.Update(dt);
		deadTimer += dt;

		if (deadTimer >= deadMaxTimer)
		{
			SetActive(false);
			deadTimer = 0.0;
			isDead = false;
			return;
		}
	}
	else
	{
		if (currentState)
		{
			currentState->Update(this, dt);
		}

		UpdateSkillTimer(dt);
		animator.Update(dt);

		sf::Vector2f beforePos = position;

		SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
		if (scene)
		{
			for (auto sprite : scene->GetMapSprites())
			{
				if (monsterType == Monsters::Spider && (sprite->GetName() == "rocks_basement" || sprite->GetName() == "grid_pit_basement") && Utils::CheckCollision(hitBox.rect, ((Obstacles*)sprite)->GetHitBox()->rect))
				{
					SetPosition(beforePos);

					float randomAngle = Utils::RandomRange(0.f, 360.f);
					float currentSpeed = Utils::Magnitude(velocity);

					float radians = randomAngle * 3.14159f / 180.f;

					velocity.x = cos(radians) * currentSpeed;
					velocity.y = sin(radians) * currentSpeed;
				}
			}

			for (auto boundary : scene->GetMapBoundary())
			{
				if (Utils::CheckCollision(hitBox.rect, boundary->rect))
				{
					SetPosition(beforePos);

					float randomAngle = Utils::RandomRange(0.f, 360.f);
					float currentSpeed = Utils::Magnitude(velocity);

					float radians = randomAngle * 3.14159f / 180.f;

					velocity.x = cos(radians) * currentSpeed;
					velocity.y = sin(radians) * currentSpeed;
				}
			}
		}

		
		position += velocity * dt;
		SetPosition(position);
	}
	


	hitBox.UpdateTransform(body, body.getLocalBounds());
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
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

	if (currentHP <= 0)
	{
		currentHP = 0;
		isDead = true;
		velocity = { 0.f,0.f };

		if(monsterType == Monsters::Fly)
		{
			animator.Play("animations/fly_dead.csv");
		}
		if (monsterType == Monsters::Spider)
		{
			animator.Play("animations/blood_small.csv");
		}
		SetOrigin(Origins::MC);
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
