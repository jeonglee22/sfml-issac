#include "stdafx.h"
#include "Isaac.h"
#include "HitBox.h"
#include "Tears.h"
#include "SceneDev2.h"
#include "SceneGame.h"
#include "Monster.h"
#include "Obstacles.h"

Isaac::Isaac(const std::string &name)
	: GameObject(name)
{
}

void Isaac::SetPosition(const sf::Vector2f &pos)
{
	position = pos;
	body.setPosition(position);
	head.setPosition(position.x, position.y - 17.f);
}

void Isaac::SetRotation(float angle)
{
	rotation = angle;
	head.setRotation(rotation);
	body.setRotation(rotation);
}

void Isaac::SetScale(const sf::Vector2f &s)
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

void Isaac::SetOrigin(const sf::Vector2f &newOrigin)
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
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
	{
		sceneGame = nullptr;
		sceneDev2 = (SceneDev2 *)SCENE_MGR.GetCurrentScene();
	}
	else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
	{
		sceneGame = (SceneGame *)SCENE_MGR.GetCurrentScene();
		sceneDev2 = nullptr;
	}

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	headAnimator.Play("animations/isaac_head_front.csv");
	bodyAnimator.Play("animations/isaac_body_idle.csv");

	for (Tears *tears : tearsList)
	{
		tears->SetActive(false);
		tearsPool.push_back(tears);
	}
	tearsList.clear();

	shootTimer = 0.0f;
	wasKeyPressed = false;
	shootDirection = {0.f, 0.f};

	SetOrigin(Origins::BC);
	SetScale({2.0f, 2.0f});
}

void Isaac::Update(float dt)
{
	headAnimator.Update(dt);
	bodyAnimator.Update(dt);

	for (auto *tears : tearsList)
	{
		if (tears->GetActive())
		{
			tears->Update(dt);
		}
	}

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

	//�浹 �� hurt �ִϸ��̼� �� �����ð� ������

	if (isHurt)
	{
		invincibleTime += dt;
		currentHurtTime += dt;

		headAnimator.Play("animations/empty.csv");
		bodyAnimator.Play("animations/isaac_hurt.csv");
		SetOrigin(Origins::BC);

		if (currentHurtTime >= maxHurtTime)
		{
			headAnimator.Play("animations/isaac_head_front.csv");
			bodyAnimator.Play("animations/isaac_body_idle.csv");
			SetOrigin(Origins::BC);
		}
		if (invincibleTime < invincibleMaxTime)
		{
			float blinkTime = fmod(invincibleTime, 0.1f);
			if (blinkTime < 0.05f)
			{
				body.setColor(sf::Color::White);
				head.setColor(sf::Color::White);
			}
			else
			{
				body.setColor(sf::Color::Transparent);
				head.setColor(sf::Color::Transparent);
			}
		}
		else
		{
			body.setColor(sf::Color::White);
			head.setColor(sf::Color::White);
			invincibleTime = 0.0f;
			currentHurtTime = 0.0f;
			isHurt = false;
		}
	}



	float h = 0.f;
	float w = 0.f;

	h = InputMgr::GetAxis(Axis::Horizontal);
	w = InputMgr::GetAxis(Axis::Vertical);

	velocity.x = h * speed;
	velocity.y = w * speed;

	sf::Vector2f beforePos = position;
	position += velocity * dt;

	SetPosition(position);

	if (h != 0.f && !isHurt)
	{
		SetScale(h > 0.f ? sf::Vector2f(2.0f, 2.0f) : sf::Vector2f(-2.0f, 2.0f));
	}

	// hitBox.UpdateTransform(head, head.getLocalBounds());
	HitBoxUpdate();

	if (sceneGame != nullptr)
	{
		for (auto sprite : sceneGame->GetMapSprites())
		{
			if (sprite->GetName() == "rocks_basement" && Utils::CheckCollision(hitBox.rect, ((Obstacles *)sprite)->GetHitBox()->rect))
			{
				SpritesPositionAtCollision(beforePos, ((Obstacles*)sprite)->GetHitBox());
			}
		}
		for (auto boundary : sceneGame->GetMapBoundary())
		{
			if (Utils::CheckCollision(hitBox.rect, boundary->rect))
			{
				SpritesPositionAtCollision(beforePos, boundary);
			}
		}
	}

	// Ani
	if (bodyAnimator.GetCurrentClipId() == "Isaac_body_idle")
	{
		if (InputMgr::GetKey(sf::Keyboard::A) || InputMgr::GetKey(sf::Keyboard::D))
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

	bool keyPressed = false;
	if (InputMgr::GetKey(sf::Keyboard::Right))
	{
		shootDirection = sf::Vector2f(1.f, 0.f);
		keyPressed = true;
	}
	else if (InputMgr::GetKey(sf::Keyboard::Left))
	{
		shootDirection = sf::Vector2f(-1.f, 0.f);
		keyPressed = true;
	}
	else if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		shootDirection = sf::Vector2f(0.f, -1.f);
		keyPressed = true;
	}
	else if (InputMgr::GetKey(sf::Keyboard::Down))
	{
		shootDirection = sf::Vector2f(0.f, 1.f);
		keyPressed = true;
	}

	if (keyPressed)
	{
		if (!wasKeyPressed || shootTimer >= shootInterval)
		{
			shootTimer = 0.f;
			FireTear(shootDirection);
			if (shootDirection.x > 0.f)
			{
				SetScale({2.f, 2.f});
				headAnimator.Play("animations/isaac_head_side_tears.csv");
			}
			if (shootDirection.x < 0.f)
			{
				SetScale({-2.f, 2.f});
				headAnimator.Play("animations/isaac_head_side_tears.csv");
			}
			if (shootDirection.y < 0.f)
			{
				headAnimator.Play("animations/isaac_head_rare_tears.csv");
			}
			if (shootDirection.y > 0.f)
			{
				headAnimator.Play("animations/isaac_head_front_tears.csv");
			}
		}
		shootTimer += dt;
		wasKeyPressed = true;
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Up) || InputMgr::GetKeyUp(sf::Keyboard::Down) || InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		headAnimator.Play("animations/isaac_head_front.csv");
	}

	MonsterCollision();

	hitBoxHead.UpdateTransform(head, head.getLocalBounds());
	hitBoxBody.UpdateTransform(body, body.getLocalBounds());
}

void Isaac::Draw(sf::RenderWindow &window)
{
	window.draw(body);
	window.draw(head);

	hitBoxHead.Draw(window);
	hitBoxBody.Draw(window);
}

void Isaac::FireTear(const sf::Vector2f &direction)
{
	if (!sceneGame)
	{
		return;
	}

	Tears *tears = nullptr;

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

	sf::Vector2f firePosition;
	if (direction.x > 0.f && direction.y == 0.f)
	{
		firePosition = {position.x + 20.f, position.y + Utils::RandomRange(-43.f, -23.f)};
	}
	else if (direction.x < 0.f && direction.y == 0.f)
	{
		firePosition = {position.x - 20.f, position.y + Utils::RandomRange(-43.f, -23.f)};
	}
	else if (direction.y < 0.f && direction.x == 0.f)
	{
		firePosition = {position.x + Utils::RandomRange(-15.f, 15.f), position.y - 50.f};
	}
	else if (direction.y > 0.f && direction.x == 0.f)
	{
		firePosition = {position.x + Utils::RandomRange(-15.f, 15.f), position.y - 20.f};
	}

	tears->Fire( firePosition, direction, 250.f, 35);
	tearsList.push_back(tears);

	sceneGame->AddGameObject(tears);
}

void Isaac::MonsterCollision()
{
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	auto monsters = scene->GetMonsters();

	sf::FloatRect isaacBounds = head.getGlobalBounds();

	for (auto& monster : monsters)
	{
		if (!monster->GetActive() || monster->IsDead())
		{
			continue;
		}

		sf::FloatRect monsterBounds = monster->GetHitBoxMonster();

		if (isaacBounds.intersects(monsterBounds) && invincibleTime == 0)
		{
			currentHP -= 50;
			std::cout << currentHP << std::endl;
			isHurt = true;
			if (currentHP <= 0)
			{
				currentHP = 0;
				SetActive(false);
			}
			return;
		}
		
	}
}

void Isaac::HitBoxUpdate()
{
	hitBox.UpdateTransform(body, body.getLocalBounds());
	hitBox.rect.setSize({ 10.f, 10.f });
	hitBox.rect.setOrigin({ 5.f, 10.f });
}

void Isaac::SpritesPositionAtCollision(const sf::Vector2f& beforePos, HitBox* box)
{
	bool XColl = false, YColl = false;

	auto currentPos = position;

	SetPosition({ beforePos.x, currentPos.y });
	HitBoxUpdate();

	YColl = Utils::CheckCollision(hitBox.rect, box->rect);

	SetPosition({ currentPos.x, beforePos.y });
	HitBoxUpdate();

	XColl = Utils::CheckCollision(hitBox.rect, box->rect);

	if (XColl)
		currentPos.x = beforePos.x;

	if (YColl)
		currentPos.y = beforePos.y;

	SetPosition(currentPos);
	HitBoxUpdate();
}

void Isaac::HitBoxUpdate()
{
	hitBox.UpdateTransform(body, body.getLocalBounds());
	hitBox.rect.setSize({ 10.f, 10.f });
	hitBox.rect.setOrigin({ 5.f, 10.f });
}

void Isaac::SpritesPositionAtCollision(const sf::Vector2f& beforePos, HitBox* box)
{
	bool XColl = false, YColl = false;

	auto currentPos = position;

	SetPosition({ beforePos.x, currentPos.y });
	HitBoxUpdate();

	YColl = Utils::CheckCollision(hitBox.rect, box->rect);

	SetPosition({ currentPos.x, beforePos.y });
	HitBoxUpdate();

	XColl = Utils::CheckCollision(hitBox.rect, box->rect);

	if (XColl)
		currentPos.x = beforePos.x;

	if (YColl)
		currentPos.y = beforePos.y;

	SetPosition(currentPos);
	HitBoxUpdate();
}
