#include "stdafx.h"
#include "Isaac.h"
#include "HitBox.h"
#include "Tears.h"
#include "SceneDev2.h"
#include "SceneGame.h"
#include "Monster.h"
#include "Door.h"
#include "Obstacles.h"
#include "Skill.h"
#include "Map.h"
#include "Bomb.h"
#include "Chest.h"

Isaac::Isaac(const std::string &name)
	: GameObject(name)
{
}

void Isaac::SetPosition(const sf::Vector2f &pos)
{
	position = pos;
	body.setPosition(position);
	head.setPosition(position.x, position.y - 20.f);

	for (auto& layer : additionalLayers)
	{
		if (layer.isActive)
		{
			layer.sprite.setPosition(position.x, position.y - 20.f);
		}
	}

	if (isDisplayingItem)
	{
		itemDisplaySprite.setPosition(position + itemDisplayOffset);
		itemEffectSprite.setPosition(position + itemDisplayOffset);
	}

	//for (sf::Sprite sprite : headAdditionals)
	//{
	//	sprite.setPosition(position.x, position.y - 20.f);
	//}
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

	for (sf::Sprite sprite : headAdditionals)
	{
		sprite.setScale(scale);
	}
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
	itemEffectAnimator.SetTarget(&itemEffectSprite);

	additionalLayers.resize(5);
	for (int i = 0; i < additionalLayers.size(); ++i)
	{
		additionalLayers[i].animator.SetTarget(&additionalLayers[i].sprite);
	}

	SetupAdditionalAnimations();
}

void Isaac::Release()
{
}

void Isaac::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
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
	sortingOrder = 3;

	headAnimator.Play("animations/isaac_head_front.csv");
	bodyAnimator.Play("animations/isaac_body_idle.csv");

	headAnimation =
	{
		{"front", "animations/isaac_head_front.csv"},
		{"side", "animations/isaac_head_side.csv"},
		{"rare", "animations/isaac_head_rare.csv"},
		{"empty", "animations/empty.csv"}
	};

	headTearsAnimation =
	{
	 {"front", "animations/isaac_head_front_tears.csv"},
	 {"side", "animations/isaac_head_side_tears.csv"},
	 {"rare", "animations/isaac_head_rare_tears.csv"}
	};

	bodyAnimation =
	{
	  {"idle", "animations/isaac_body_idle.csv"},
	  {"run_weight", "animations/isaac_run_weight.csv"},
	  {"run_height", "animations/isaac_run_height.csv"},
	  {"hurt", "animations/isaac_hurt.csv"},
	  {"dead", "animations/isaac_dead.csv" },
	  {"happy", "animations/isaac_happy.csv"}
	};


	for (Tears *tears : tearsList)
	{
		tears->SetActive(false);
		tearsPool.push_back(tears);
	}
	tearsList.clear();

	for (Bomb* bomb : bombsList)
	{
		bomb->SetActive(false);
		bombsPool.push_back(bomb);
	}
	bombsList.clear();

	shootTimer = 0.0f;
	wasKeyPressed = false;
	currentHP = inventory.heartCount;

	isGettingItem = false;
	itemAnimationTime = 0.0f;
	isDisplayingItem = false;

	isDead = false;

	SetOrigin(Origins::BC);
	SetScale({2.0f, 2.0f});
}

void Isaac::Update(float dt)
{
	if(activeSkill != nullptr)
	{
		activeSkill->Update(dt);
	}

	ClampItemCounts();

	headAnimator.Update(dt);
	bodyAnimator.Update(dt);

	for (auto& layer : additionalLayers)
	{
		if (layer.isActive)
		{
			layer.animator.Update(dt);
		}
	}

	if (isDisplayingItem)
	{
		itemEffectAnimator.Update(dt);
	}

	UpdateItemDisplay(dt);

	if (isDead)
	{
		return;
	}

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

	for (auto* bomb : bombsList)
	{
		if (bomb->GetActive())
		{
			bomb->Update(dt);
		}
	}

	auto bombIt = bombsList.begin();
	while (bombIt != bombsList.end())
	{
		if (!(*bombIt)->GetActive())
		{
			bombsPool.push_back(*bombIt);
			bombIt = bombsList.erase(bombIt);
		}
		else
		{
			++bombIt;
		}
	}

	if (isGettingItem)
	{
		itemAnimationTime += dt;

		if (itemAnimationTime < itemAnimationMaxTime)
		{
			PlayHeadAnimation("empty");
			PlayBodyAnimation("happy");
		}
		else
		{
			PlayHeadAnimation("front");
			PlayBodyAnimation("idle");

			itemAnimationTime = 0.0f;
			isGettingItem = false;
		}
	}

	if (isHurt)
	{
		invincibleTime += dt;
		currentHurtTime += dt;

		PlayHeadAnimation("empty");
		PlayBodyAnimation("hurt");
		SetOrigin(Origins::BC);

		if (currentHurtTime >= maxHurtTime)
		{
			PlayHeadAnimation("front");
			PlayBodyAnimation("idle");
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

	HitBoxUpdate();

	if (sceneGame != nullptr)
	{
		for (auto sprite : sceneGame->GetMapSprites())
		{
			if ((sprite->GetName() == "rocks_basement" || sprite->GetName() == "grid_pit_basement") 
				&& Utils::CheckCollision(hitBoxBody.rect, ((Obstacles*)sprite)->GetHitBox()->rect) && sprite->GetActive())
			{
				SpritesPositionAtCollision(beforePos, ((Obstacles*)sprite)->GetHitBox());
			}
			if (sprite->GetName() == "grid_spikes" && Utils::CheckCollision(hitBoxBody.rect, ((Obstacles*)sprite)->GetHitBox()->rect))
			{
				if (invincibleTime == 0)
				{
					TakeDamage(1);
					break;
				}
			}
		}
		for (auto boundary : sceneGame->GetMapBoundary())
		{
			if (Utils::CheckCollision(hitBoxBody.rect, boundary->rect))
			{
				SpritesPositionAtCollision(beforePos, boundary);
			}
		}
		for (auto door : sceneGame->GetMapDoor())
		{
			if (!door->GetMapCleared() && Utils::CheckCollision(hitBoxBody.rect, door->GetHitBox()->rect))
			{
				bool currentMapCleared = sceneGame->GetCurrentMap()->GetCleared();
				if (currentMapCleared && door->GetDoorLocked() && inventory.keyCount > 0 && !door->GetDoorStart())
				{
					inventory.keyCount--;
					door->PlayUnlock();
				}
				SpritesPositionAtCollision(beforePos, door->GetHitBox());
			}
		}
	}

	shootTimer += dt;
	bool shootingKeyPressed = false;
	sf::Vector2f shootInput = { 0.f, 0.f };
	sf::Vector2f finalShootDirection = { 0.f, 0.f };

	if (InputMgr::GetKey(sf::Keyboard::Right))
	{
		shootInput = sf::Vector2f(1.f, 0.f);
		shootingKeyPressed = true;
	}
	else if (InputMgr::GetKey(sf::Keyboard::Left))
	{
		shootInput = sf::Vector2f(-1.f, 0.f);
		shootingKeyPressed = true;
	}
	else if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		shootInput = sf::Vector2f(0.f, -1.f);
		shootingKeyPressed = true;
	}
	else if (InputMgr::GetKey(sf::Keyboard::Down))
	{
		shootInput = sf::Vector2f(0.f, 1.f);
		shootingKeyPressed = true;
	}

	if (shootingKeyPressed)
	{
		finalShootDirection = shootInput;

		if (abs(h) > 0.1f || abs(w) > 0.1f)
		{
			sf::Vector2f moveDirection = { h, w };

			float influence = 0.3f;
			finalShootDirection.x += moveDirection.x * influence;
			finalShootDirection.y += moveDirection.y * influence;

			float length = sqrt(finalShootDirection.x * finalShootDirection.x +
				finalShootDirection.y * finalShootDirection.y);
			if (length > 0)
			{
				finalShootDirection.x /= length;
				finalShootDirection.y /= length;
			}
		}


		if (!isHurt && !isGettingItem)
		{
			if (shootInput.x > 0.f)
			{
				head.setScale({ 2.f, 2.f });
				head.setPosition(position.x, position.y - 19.f);
				PlayHeadTearsAnimation("side");
			}
			else if (shootInput.x < 0.f)
			{
				head.setScale({ -2.f, 2.f });
				PlayHeadTearsAnimation("side");
				head.setPosition(position.x, position.y - 19.f);
			}
			else if (shootInput.y < 0.f)
			{
				head.setScale(body.getScale());
				head.setPosition(position.x, position.y - 19.f);
				PlayHeadTearsAnimation("rare");
			}
			else if (shootInput.y > 0.f)
			{
				head.setScale(body.getScale());
				head.setPosition(position.x, position.y - 19.f);
				PlayHeadTearsAnimation("front");

			}
			if (abs(h) > 0.1f || abs(w) > 0.1f)
			{
				if (w < 0.f)
				{
					PlayBodyAnimation("run_height");
				}
				else if (w > 0.f)
				{
					PlayBodyAnimation("run_height");
				}
				else if (h != 0.f)
				{
					PlayBodyAnimation("run_weight");
				}
			}
			else
			{
				PlayBodyAnimation("idle");
			}
		}
		if (shootTimer >= shootInterval)
		{
			FireTear(finalShootDirection);
			SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear fire 4.wav"));
			shootTimer = 0.f;
		}
		shootTimer += dt;
		wasKeyPressed = true;
	}
	else
	{
		if (!InputMgr::GetKey(sf::Keyboard::Right) &&
			!InputMgr::GetKey(sf::Keyboard::Left) &&
			!InputMgr::GetKey(sf::Keyboard::Up) &&
			!InputMgr::GetKey(sf::Keyboard::Down))
		{
			wasKeyPressed = false;
		}
		if (!isHurt && !isGettingItem)
		{
			head.setScale(body.getScale());

			if (h == 0.f && w == 0.f)
			{
				PlayHeadAnimation("front");
				PlayBodyAnimation("idle");
			}
			else
			{
				if (w < 0.f)
				{
					PlayHeadAnimation("rare");
					PlayBodyAnimation("run_height");
				}
				else if (w > 0.f)
				{
					PlayHeadAnimation("front");
					PlayBodyAnimation("run_height");
				}
				else if (h != 0.f)
				{
					PlayHeadAnimation("side");
					PlayBodyAnimation("run_weight");
				}
			}
		}
	}

	if (!isHurt && !isGettingItem && (InputMgr::GetKeyUp(sf::Keyboard::Up) || InputMgr::GetKeyUp(sf::Keyboard::Down) || InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right)))
	{
		float currentH = InputMgr::GetAxis(Axis::Horizontal);
		float currentW = InputMgr::GetAxis(Axis::Vertical);

		if (currentH == 0.f && currentW == 0.f)
		{
			PlayHeadAnimation("front");
			PlayBodyAnimation("idle");
		}
		else
		{

			if (currentW < 0.f)
			{
				PlayHeadAnimation("rare");
				PlayBodyAnimation("run_height");
			}
			else if (currentW > 0.f)
			{
				PlayHeadAnimation("front");
				PlayBodyAnimation("run_height");
			}
			else if (currentH != 0.f)
			{
				PlayHeadAnimation("side");
				PlayBodyAnimation("run_weight");
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::E) && inventory.bombCount > 0)
	{
		InstallBomb();
	}
#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		inventory.coinCount++;
		inventory.keyCount++;
		inventory.bombCount++;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num8))
	{
		inventory.coinCount--;
		inventory.keyCount--;
		inventory.bombCount--;
	}
#endif DEF_DEV
	ChangeAnimation();
	ChestCollision();
	MonsterCollision();

	HitBoxUpdate();
}

void Isaac::Draw(sf::RenderWindow &window)
{
	window.draw(body);
	window.draw(head);

	for (const auto& layer : additionalLayers)
	{
		if (layer.isActive)
		{
			window.draw(layer.sprite);
		}
	}

	if (isDisplayingItem)
	{
		window.draw(itemEffectSprite);
		window.draw(itemDisplaySprite);
	}

	hitBoxHead.Draw(window);
	hitBoxBody.Draw(window);
}

void Isaac::FireTear(const sf::Vector2f &direction)
{
	if (!sceneGame)
	{
		return;
	}

	std::vector<Tears*> tears;
	
	int doBackShoot = 0;
	if(isBackShoot)
		doBackShoot = Utils::RandomRange(0.f, 1.f) <= 0.5f ? 1 : 0;

	for(int i = 0; i < tearCount + doBackShoot; i++)
	{
		Tears* tear = nullptr;

		if (tearsPool.empty())
		{
			tear = new Tears();
			tear->Init();
		}
		else
		{
			tear = tearsPool.front();
			tearsPool.pop_front();
			tear->SetActive(true);
		}

		tear->Reset();
		tears.push_back(tear);
	}

	sf::Vector2f firePosition = position;

	if (direction.x > 0.1f)
	{
		firePosition.x += 20.f;
	}
	else if (direction.x < -0.1f)
	{
		firePosition.x -= 20.f;
	}

	if (direction.y > 0.1f)
	{
		firePosition.y += Utils::RandomRange(-20.f, 0.f);
	}
	else if (direction.y < -0.1f)
	{
		firePosition.y += Utils::RandomRange(-50.f, -30.f);
	}
	else
	{
		firePosition.y += Utils::RandomRange(-43.f, -23.f);
	}

	for (int i = 0; i < tearCount + doBackShoot; i++)
	{
		if (tearCount == 1)
			tears[i]->Fire(firePosition, direction, tearSpeed, (int)std::round(tearDamage));
		else if (tearCount == 3)
		{
			sf::Vector2f newfirePos = firePosition;
			float angle = Utils::Angle(direction);
			sf::Vector2f newDirection = Utils::GetNormal(sf::Vector2f(std::cos(Utils::DegreeToRadian(angle + 3 * (i - 1))), std::sin(Utils::DegreeToRadian(angle + 3 * (i - 1)))));
			if (direction.x != 0.f)
			{
				newfirePos.y += (direction.x > 0 ? -1.f : 1.f) * (1 - i) * 10.f;
			}
			if (direction.y != 0.f)
			{
				newfirePos.x += (direction.y < 0 ? -1.f : 1.f) * (1 - i) * 10.f;
			}
			tears[i]->Fire(newfirePos, newDirection, tearSpeed, (int)std::round(tearDamage));
		}
		if (i == tearCount)
		{
			tears[i]->Fire(firePosition, direction * -1.f, tearSpeed, (int)std::round(tearDamage));
		}
		tearsList.push_back(tears[i]);
		sceneGame->AddGameObject(tears[i]);
	}
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
			TakeDamage(1);
			return;
		}
		
	}
}

void Isaac::ChestCollision()
{
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	auto chests = scene->GetChests();

	sf::FloatRect isaacBounds = body.getGlobalBounds();

	for (auto& chest : chests)
	{
		if (chest->IsOpen())
		{
			continue;
		}

		sf::FloatRect chestBounds = chest->GetHitBoxChest();

		if (isaacBounds.intersects(chestBounds))
		{
			if (chest->GetChestType() == ChestType::Normal)
			{
				chest->ChestOpen();
				break;
			}
			if (chest->GetChestType() == ChestType::Gold && inventory.keyCount > 0)
			{
				chest->ChestOpen();
				inventory.keyCount--;
				break;
			}
		}

	}


}

void Isaac::HitBoxUpdate()
{
	hitBoxHead.UpdateTransform(head, head.getLocalBounds());
	hitBoxHead.rect.setSize({ 20.f, 20.f });
	hitBoxHead.rect.setOrigin({ 10.f, 25.f });
	hitBoxBody.UpdateTransform(body, body.getLocalBounds());
	hitBoxBody.rect.setSize({ 10.f, 10.f });
	hitBoxBody.rect.setOrigin({ 5.f, 20.f });
}

void Isaac::SpritesPositionAtCollision(const sf::Vector2f& beforePos, HitBox* box)
{
	bool XColl = false, YColl = false;

	auto currentPos = position;

	SetPosition({ beforePos.x, currentPos.y });
	HitBoxUpdate();

	YColl = Utils::CheckCollision(hitBoxBody.rect, box->rect);

	SetPosition({ currentPos.x, beforePos.y });
	HitBoxUpdate();

	XColl = Utils::CheckCollision(hitBoxBody.rect, box->rect);

	if (XColl)
		currentPos.x = beforePos.x;

	if (YColl)
		currentPos.y = beforePos.y;

	SetPosition(currentPos);
	HitBoxUpdate();
}

void Isaac::TakeDamage(int damage)
{
	currentHP -= damage;
	SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/hurt grunt " + std::to_string(Utils::RandomRange(1, 3)) + ".wav"));
	isHurt = true;
	if (currentHP <= 0)
	{
		currentHP = 0;
		isDead = true;
		PlayHeadAnimation("empty");
		PlayBodyAnimation("dead");
		SetOrigin(Origins::BC);
	}
}

void Isaac::PlayHeadAnimation(const std::string& animation)
{
	auto it = headAnimation.find(animation);
	if (it != headAnimation.end() && currentHeadAnimation != animation)
	{
		headAnimator.Play(it->second);
		currentHeadAnimation = animation;

		UpdateAdditionalAnimations(animation);
	}
}

void Isaac::PlayHeadTearsAnimation(const std::string& animation)
{
	auto it = headTearsAnimation.find(animation);
	if (it != headTearsAnimation.end() && currentHeadAnimation != ("tears_" + animation))
	{
		headAnimator.Play(it->second);
		currentHeadAnimation = "tears_" + animation;

		UpdateAdditionalAnimations("tears_" + animation);
	}
}

void Isaac::PlayBodyAnimation(const std::string& animation)
{
	auto it = bodyAnimation.find(animation);
	if (it != bodyAnimation.end() && currentBodyAnimation != animation)
	{
		bodyAnimator.Play(it->second);
		currentBodyAnimation = animation;
	}
}

bool Isaac::IsCurrentHeadAnimation(const std::string& animation) const
{
	return currentHeadAnimation == animation;
}

bool Isaac::IsCurrentBodyAnimation(const std::string& animation) const
{
	return currentBodyAnimation == animation;
}

void Isaac::AddItem(Items itemType)
{
	switch (itemType)
	{
	case Items::Heart:
		currentHP = std::min(currentHP + 2, maxHP);
		inventory.heartCount = currentHP;
		break;
	case Items::Half_Heart:
		currentHP = std::min(currentHP + 1, maxHP);
		inventory.heartCount = currentHP;
		break;
	case Items::Coin:
		inventory.coinCount++;
		break;
	case Items::Bomb:
		inventory.bombCount++;
		break;
	case Items::Key:
		inventory.keyCount++;
		break;
	}
}

void Isaac::InstallBomb()
{
	if (inventory.bombCount <= 0)
	{
		return;
	}

	Bomb* bomb = nullptr;

	if (bombsPool.empty())
	{
		bomb = new Bomb();
		bomb->Init();
	}
	else
	{
		bomb = bombsPool.front();
		bombsPool.pop_front();
		bomb->SetActive(true);
	}

	bomb->Reset();
	bomb->SetPosition(position - sf::Vector2f(0, bomb->GetLocalBounds().getSize().y));
	bombsList.push_back(bomb);

	inventory.bombCount--;
	sceneGame->AddGameObject(bomb);
}

void Isaac::ClampItemCounts()
{
	inventory.bombCount = Utils::Clamp(inventory.bombCount, 0, 100);
	inventory.keyCount = Utils::Clamp(inventory.keyCount, 0, 100);
	inventory.coinCount = Utils::Clamp(inventory.coinCount, 0, 100);
	inventory.heartCount = Utils::Clamp(inventory.heartCount, 0, 100);
}

void Isaac::ChangeAnimation()
{
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	for (Skill* skill : passiveSkill)
	{
		if (skill->GetTextId() == "graphics/additionals/collectibles/collectibles_006_numberone.png")
		{
			headAnimation =
			{
				{"front", "animations/isaac_head_front_number_one.csv"},
				{"side", "animations/isaac_head_side_number_one.csv"},
				{"rare", "animations/isaac_head_rare_number_one.csv"},
				{"empty", "animations/empty.csv"}
			};
			headTearsAnimation =
			{
				{"front", "animations/isaac_head_front_tears_number_one.csv"},
				{"side", "animations/isaac_head_side_tears_number_one.csv"},
				{"rare", "animations/isaac_head_rare_tears_number_one.csv"}
			};
		}
		else if (skill->GetTextId() == "graphics/additionals/collectibles/collectibles_004_cricketshead.png")
		{
			headAnimation =
			{
				{"front", "animations/isaac_head_front_c_head.csv"},
				{"side", "animations/isaac_head_side_c_head.csv"},
				{"rare", "animations/isaac_head_rare_c_head.csv"},
				{"empty", "animations/empty.csv"}
			};
			headTearsAnimation =
			{
				{"front", "animations/isaac_head_front_tears_c_head.csv"},
				{"side", "animations/isaac_head_side_tears_c_head.csv"},
				{"rare", "animations/isaac_head_rare_tears_c_head.csv"}
			};
		}
		else if (skill->GetTextId() == "graphics/additionals/collectibles/collectibles_055_momseye.png")
		{
			headAnimation =
			{
				{"front", "animations/isaac_head_front_momseye.csv"},
				{"side", "animations/isaac_head_side_momseye.csv"},
				{"rare", "animations/isaac_head_rare_momseye.csv"},
				{"empty", "animations/empty.csv"}
			};
			headTearsAnimation =
			{
				{"front", "animations/isaac_head_front_tears_momseye.csv"},
				{"side", "animations/isaac_head_side_tears_momseye.csv"},
				{"rare", "animations/isaac_head_rare_tears_momseye.csv"}
			};
		}
	}
}

void Isaac::DisplayItem(const std::string& textureId)
{
	itemDisplaySprite.setTexture(TEXTURE_MGR.Get(textureId));

	Utils::SetOrigin(itemDisplaySprite, Origins::MC);
	itemDisplaySprite.setScale({ 2.0f, 2.0f });
	itemDisplaySprite.setPosition(position + itemDisplayOffset);

	itemEffectAnimator.Play("animations/star_effect.csv");
	Utils::SetOrigin(itemEffectSprite, Origins::MC);
	itemEffectSprite.setScale({ 2.2f, 2.2f });
	itemEffectSprite.setPosition(position + itemDisplayOffset);

	isDisplayingItem = true;
	itemDisplayTime = 0.0f;

	isGettingItem = true;
	itemAnimationTime = 0.0f;
}

void Isaac::UpdateItemDisplay(float dt)
{
	if (!isDisplayingItem)
	{
		return;
	}

	itemDisplayTime += dt;

	itemDisplaySprite.setPosition(position + itemDisplayOffset);
	itemEffectSprite.setPosition(position + itemDisplayOffset);

	if (itemDisplayTime >= itemDisplayMaxTime)
	{
		isDisplayingItem = false;
		itemDisplayTime = 0.0f;
	}
}

void Isaac::SetupAdditionalAnimations()
{
	additionalAnimations["bloodofthemartyr"] = {
		{"front", "animations/isaac_head_front_martyr.csv"},
		{"side", "animations/isaac_head_side_martyr.csv"},
		{"rare", "animations/isaac_head_rare_martyr.csv"},
		{"tears_front", "animations/isaac_head_front_tears_martyr.csv"},
		{"tears_side", "animations/isaac_head_side_tears_martyr.csv"},
		{"tears_rare", "animations/isaac_head_rare_tears_martyr.csv"}
	};

	additionalAnimations["boom"] = {
		{"front", "animations/isaac_head_front_boom.csv"},
		{"side", "animations/isaac_head_side_boom.csv"},
		{"rare", "animations/isaac_head_rare_boom.csv"},
		{"tears_front", "animations/isaac_head_front_tears_boom.csv"},
		{"tears_side", "animations/isaac_head_side_tears_boom.csv"},
		{"tears_rare", "animations/isaac_head_rare_tears_boom.csv"}
	};

	additionalAnimations["theinnereye"] = {
	{"front", "animations/isaac_head_front_innereye.csv"},
	{"side", "animations/isaac_head_side_innereye.csv"},
	{"rare", "animations/isaac_head_rare_innereye.csv"},
	{"tears_front", "animations/isaac_head_front_tears_innereye.csv"},
	{"tears_side", "animations/isaac_head_side_tears_innereye.csv"},
	{"tears_rare", "animations/isaac_head_rare_tears_innereye.csv"}
	};

	additionalAnimations["sadonion"] = {
	{"front", "animations/isaac_head_front_sadonion.csv"},
	{"side", "animations/isaac_head_side_sadonion.csv"}
	};

}

void Isaac::AddAdditionalItem(const std::string& itemId)
{
	if (itemToLayerIndex.find(itemId) != itemToLayerIndex.end())
	{
		return;
	}

	for (int i = 0; i < additionalLayers.size(); ++i)
	{
		if (!additionalLayers[i].isActive)
		{
			additionalLayers[i].isActive = true;
			additionalLayers[i].itemId = itemId;

			if (additionalAnimations.find(itemId) != additionalAnimations.end())
			{
				additionalLayers[i].animator.Play(additionalAnimations[itemId]["front"]);
			}

			additionalLayers[i].sprite.setPosition(head.getPosition());
			additionalLayers[i].sprite.setScale(head.getScale());
			Utils::SetOrigin(additionalLayers[i].sprite, Origins::MC);

			itemToLayerIndex[itemId] = i;

			break;
		}
	}
}

void Isaac::RemoveAdditionalItem(const std::string& itemId)
{
	auto it = itemToLayerIndex.find(itemId);
	if (it != itemToLayerIndex.end())
	{
		int layerIndex = it->second;
		additionalLayers[layerIndex].isActive = false;
		additionalLayers[layerIndex].itemId = "";
		itemToLayerIndex.erase(it);

	}
}

void Isaac::UpdateAdditionalAnimations(const std::string& direction)
{
	for (auto& layer : additionalLayers)
	{
		if (layer.isActive)
		{
			auto itemAnimations = additionalAnimations.find(layer.itemId);
			if (itemAnimations != additionalAnimations.end())
			{
				auto animationPath = itemAnimations->second.find(direction);
				if (animationPath != itemAnimations->second.end())
				{
					layer.animator.Play(animationPath->second);
				}
			}

			layer.sprite.setPosition(head.getPosition());
			layer.sprite.setScale(head.getScale());
		}
	}
}
