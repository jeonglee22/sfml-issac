#include "stdafx.h"
#include "Tears.h"
#include "SceneGame.h"
#include "Monster.h"
#include "Animator.h"
#include "Obstacles.h"
#include "LarryJr.h"

std::string Tears::tearIdle = "animations/tears_idle.csv";
std::string Tears::tearBoom = "animations/tears_boom.csv";
sf::Color Tears::tearColor = sf::Color::White;
float Tears::maxRange = 300.f;

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
	animator.Play(tearIdle);

	tearsCrushTime = 0.0f;
	isTearsCrush = false;
	damage = 35;
	hasReachedMaxRange = false;

	Utils::SetOrigin(sprite, Origins::MC);
	sprite.setColor(tearColor);
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

	if (!hasReachedMaxRange && distance > maxRange)
	{
		maxRangePosition = position;
		hasReachedMaxRange = true;
	}

	SetPosition(position + velocity * dt);
	float scale = Utils::Clamp((damage / (float)initDamage) * 1.5f, 0.5f, 2.5f);
	SetScale( {scale,scale});
	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());

	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (scene)
	{
		for (auto sprite : scene->GetMapSprites())
		{
			if (sprite->GetName() == "rocks_basement" && Utils::CheckCollision(hitBox.rect, ((Obstacles*)sprite)->GetHitBox()->rect))
			{
				StartSplash();
				SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
				SetOrigin(Origins::MC);
				return;
			}
		}

		for (auto boundary : scene->GetMapTearBoundary())
		{
			if (Utils::CheckCollision(hitBox.rect, boundary->rect))
			{
				StartSplash();
				SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
				SetOrigin(Origins::MC);
				return;
			}
		}
	}


	float allowedDrop = 30.f;

	if (hasReachedMaxRange)
	{
		if (abs(direction.x) > 0.1f && position.y > maxRangePosition.y + allowedDrop)
		{
			StartSplash();
			SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/splatter 2.wav"));
			SetOrigin(Origins::MC);
			return;
		}
	}

	Hit();
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
			SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
			SetOrigin(Origins::MC);
			isTearsCrush = true;
			return;
		}

		LarryJr* larry = dynamic_cast<LarryJr*>(monster);
		if (larry != nullptr)
		{
			for (const auto& segment : larry->bodySegments)
			{
				if (isaacBounds.intersects(segment.BodyHitBox()))
				{
					monster->TakeDamage(damage);
					StartSplash();
					SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear block.wav"));
					SetOrigin(Origins::MC);
					isTearsCrush = true;
					return;
				}
			}
		}

	}

}

void Tears::StartSplash()
{
	if (isTearsCrush)
	{
		return;
	}

	animator.Play(tearBoom);

	isTearsCrush = true;
	tearsCrushTime = 0.0f;
	damage = 0;

	velocity = { 0.f, 0.f };
}


