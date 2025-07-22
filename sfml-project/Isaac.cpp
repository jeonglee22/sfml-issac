#include "stdafx.h"
#include "Isaac.h"
#include "HitBox.h"
#include "Tears.h"

Isaac::Isaac(const std::string& name)
	: GameObject(name)
{
}

void Isaac::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	head.setPosition(position.x, position.y - 13.f);
}

void Isaac::SetRotation(float angle)
{
	rotation = angle;
	head.setRotation(rotation);
	body.setRotation(rotation);
}

void Isaac::SetScale(const sf::Vector2f& s)
{
	scale = s;
	head.setScale(scale);
	body.setScale(scale);
}

void Isaac::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(head, originPreset);
		Utils::SetOrigin(body, originPreset);
	}
}

void Isaac::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
	origin = Utils::SetOrigin(head, originPreset);
}

void Isaac::Init()
{
	headAnimator.SetTarget(&head);
	bodyAnimator.SetTarget(&body);
}

void Isaac::Release()
{
}

void Isaac::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	headAnimator.Play("animations/isaac_head_front.csv");
	bodyAnimator.Play("animations/isaac_body_idle.csv");

	for (Tears* tears : tearsList)
	{
		tears->SetActive(false);
		tearsPool.push_back(tears);
	}
	tearsList.clear();

	SetScale({ 2.0f, 2.0f });
	SetOrigin(Origins::BC);
}

void Isaac::Update(float dt)
{
	headAnimator.Update(dt);
	bodyAnimator.Update(dt);

	auto it = tearsList.begin();
	while (it != tearsList.end())
	{
		if (!(*it)->GetActive())
		{
			tearsPool.push_back(*it);
			it = tearsList.erase(it);
		}
		else
		{
			++it;
		}
	}

	float h = 0.f;
	float w = 0.f;

	h = InputMgr::GetAxis(Axis::Horizontal);
	w = InputMgr::GetAxis(Axis::Vertical);

	velocity.x = h * speed;
	velocity.y = w * speed;

	position += velocity * dt;

	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(2.0f, 2.0f) : sf::Vector2f(-2.0f, 2.0f));
	}

	// Ani
	if (bodyAnimator.GetCurrentClipId() == "Isaac_body_idle")
	{
		if (h != 0.f)
		{
			bodyAnimator.Play("animations/isaac_run_weight.csv");
			headAnimator.Play("animations/isaac_head_side.csv");
		}
		else if (w != 0.f)
		{
			bodyAnimator.Play("animations/isaac_run_height.csv");
			if (w < 0.f)
			{
				headAnimator.Play("animations/isaac_head_rare.csv");
			}
		}
		
	}
	else if (bodyAnimator.GetCurrentClipId() == "Isaac_run_height" || bodyAnimator.GetCurrentClipId() == "Isaac_run_weight")
	{
		if (w == 0.f && h == 0.f)
		{
			bodyAnimator.Play("animations/isaac_body_idle.csv");
			headAnimator.Play("animations/isaac_head_front.csv");
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		Tears* tears = nullptr;
		if (tearsPool.empty())
		{
			tears = new Tears();
			tears->Init();
		}
		else
		{
			tears = tearsPool.front();
			tearsPool.pop_front();
			tears->SetActive(true);
		}

		tears->Reset();
		tears->Fire(position * 10.f, velocity, 1000.f, 10);

		tearsList.push_back(tears);
	}






	hitBox.UpdateTransform(head, head.getLocalBounds());
	//hitBox.UpdateTransform(body, body.getLocalBounds());
}

void Isaac::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(head);

	hitBox.Draw(window);
}
