#include "stdafx.h"
#include "Monster.h"
#include "MonsterState.h"
#include "Obstacles.h"
#include "SceneGame.h"
#include "spider.h"
#include "Fly.h"
#include "Hopper.h"
#include "Body.h"

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

		sf::Vector2f currentPos = position;
		sf::Vector2f newPos = position + velocity * dt;

		bool isHopperJumping = (monsterType == Monsters::Hopper && currentState && currentState->GetStateName() == "HopperJump");

		if (!isHopperJumping && WillCollideAt(newPos))
		{
			sf::Vector2f safeVelocity = GetSafeDirection(currentPos, velocity);
			velocity = safeVelocity;
			newPos = position + velocity * dt;

			HandleCollisionByType();
		}
		else if (isHopperJumping && WillCollideAt(newPos))
		{
			HandleHopperJumpCollision();
		}

		position = newPos;
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
		if (monsterType == Monsters::Body)
		{
			animator.Play("animations/blood_small.csv");
		}
		SOUND_MGR.StopAllSfx();
		SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/death burst small.wav"));
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

bool Monster::WillCollideAt(const sf::Vector2f& testPos)
{
	sf::Vector2f originalPos = position;
	SetPosition(testPos);
	if (monsterType == Monsters::Hopper)
	{
		sf::FloatRect newHitBox = GetHitBoxMonster();
		hitBox.rect.setPosition(newHitBox.left, newHitBox.top);
		hitBox.rect.setSize(sf::Vector2f(newHitBox.width, newHitBox.height));
	}
	else
	{
		hitBox.UpdateTransform(body, body.getLocalBounds());
	}

	bool willCollide = false;
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene)
	{
		for (auto boundary : scene->GetMapBoundary())
		{
			if (Utils::CheckCollision(hitBox.rect, boundary->rect))
			{
				willCollide = true;
				break;
			}
		}

		if (!willCollide && (monsterType == Monsters::Spider || monsterType == Monsters::Hopper || monsterType == Monsters::Body))
		{
			for (auto sprite : scene->GetMapSprites())
			{
				if ((sprite->GetName() == "rocks_basement" || sprite->GetName() == "grid_pit_basement") &&
					Utils::CheckCollision(hitBox.rect, ((Obstacles*)sprite)->GetHitBox()->rect))
				{
					willCollide = true;
					break;
				}
			}
		}
	}

	SetPosition(originalPos);
	if (monsterType == Monsters::Hopper)
	{
		sf::FloatRect newHitBox = GetHitBoxMonster();
		hitBox.rect.setPosition(newHitBox.left, newHitBox.top);
		hitBox.rect.setSize(sf::Vector2f(newHitBox.width, newHitBox.height));
	}
	else
	{
		hitBox.UpdateTransform(body, body.getLocalBounds());
	}

	return willCollide;
}

sf::Vector2f Monster::GetSafeDirection(const sf::Vector2f& currentPos, const sf::Vector2f& currentVel)
{
	static const sf::Vector2f directions[8] = {
		{1.0f, 0.0f},
		{0.707f, 0.707f},
		{0.0f, 1.0f},
		{-0.707f, 0.707f},
		{-1.0f, 0.0f},
		{-0.707f, -0.707f},
		{0.0f, -1.0f},
		{0.707f, -0.707f}
	};

	float currentSpeed = Utils::Magnitude(currentVel);
	if (currentSpeed < 10.0f) currentSpeed = 30.0f;

	for (int i = 0; i < 8; i++)
	{
		sf::Vector2f testVelocity = directions[i] * currentSpeed;
		sf::Vector2f testPos = currentPos + testVelocity * 0.016f;

		if (!WillCollideAt(testPos))
		{
			return testVelocity;
		}
	}

	return sf::Vector2f(0, 0);
}

void Monster::HandleCollisionByType()
{
	if (monsterType == Monsters::Spider)
	{
		Spider* spider = static_cast<Spider*>(this);
		spider->ChangeToPatrolState();
	}
	else if (monsterType == Monsters::Body)
	{
		Body* body = static_cast<Body*>(this);
		body->SetInitialState();
	}
	//else if (monsterType == Monsters::Hopper)
	//{
	//	Hopper* hopper = static_cast<Hopper*>(this);
	//	hopper->ChangeToIdleState();
	//}
	else
	{
		Fly* fly = static_cast<Fly*>(this);
		fly->SetInitialState();
	}
}

void Monster::HandleHopperJumpCollision()
{
	if (monsterType == Monsters::Hopper)
	{
		Hopper* hopper = static_cast<Hopper*>(this);

		sf::Vector2f currentDirection = velocity;
		float speed = Utils::Magnitude(currentDirection);
		if (speed > 0) {
			currentDirection = currentDirection / speed;
		}
		else {
			currentDirection = sf::Vector2f(-1.0f, 0.0f);
		}

		sf::Vector2f bounceVelocity = -currentDirection * (speed * 0.6f);
		velocity = bounceVelocity;

		hopper->ChangeToIdleState();
	}
}
