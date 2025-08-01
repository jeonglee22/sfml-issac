#include "stdafx.h"
#include "Door.h"

Door::Door(MapType type, const std::string& name)
	:SpriteGo("", name), type(type)
{
	switch (type)
	{
	case MapType::Normal:
	case MapType::Rectangle:
	case MapType::Large:
	case MapType::Start:
	case MapType::Special:
		this->textureId = "graphics/additionals/door_01_normaldoor.png";
		doorTextureRect = { 8, 9, 49, 33 };
		break;
	case MapType::Boss:
		textureId = "graphics/additionals/door_10_bossroomdoor.png";
		doorTextureRect = {2,3,61,39};
		break;
	case MapType::Hidden:
		textureId = "graphics/effects/holeinwall.png";
		doorTextureRect = { 0, 0, 49, 42 };
		break;
	case MapType::Shop:
		textureId = "graphics/additionals/door_01_normaldoor.png";
		doorTextureRect = { 8, 9, 49, 33 };
		doorClosedRightRect = { 84, 112, 25, 23 };
		break;
	case MapType::Treasure:
		textureId = "graphics/additionals/door_02_treasureroomdoor.png";
		doorTextureRect = { 8, 4, 49, 38 };
		break;
	case MapType::Sacrifice:
		textureId = "graphics/additionals/door_04_selfsacrificeroomdoor.png";
		doorTextureRect = { 8, 9, 49, 33 };
		break;
	default:
		textureId = "";
		break;
	}
}

void Door::SetPosition(const sf::Vector2f& pos)
{
	SpriteGo::SetPosition(pos);
	doorOpened.setPosition(pos + doorOffset);
	doorClosedLeft.setPosition(pos + doorOffset);
	doorClosedRight.setPosition(pos + doorOffset);
	key->setPosition(pos);
}

void Door::SetRotation(float rot)
{
	SpriteGo::SetRotation(rot);
	doorOpened.setRotation(rot);
	doorClosedLeft.setRotation(rot);
	doorClosedRight.setRotation(rot);
	key->setRotation(rot);
}

void Door::SetScale(const sf::Vector2f& s)
{
	SpriteGo::SetScale(s);
	doorOpened.setScale(s);
	doorClosedLeft.setScale(s);
	doorClosedRight.setScale(s);
	key->setScale(s);
	if(type == MapType::Boss)
	{
		doorOpened.setScale({s.x * 1.5f, s.y});
		doorClosedLeft.setScale({ s.x * 1.5f, s.y });
		doorClosedRight.setScale({ s.x * 1.5f, s.y });
	}
	
}

void Door::SetOrigin(const sf::Vector2f& o)
{
	SpriteGo::SetOrigin(o);
	doorOpened.setOrigin(o);
	doorClosedLeft.setOrigin(o);
	doorClosedRight.setOrigin(o);
	key->setOrigin(o);
}

void Door::SetOrigin(Origins preset)
{
	SpriteGo::SetOrigin(preset);
}

void Door::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 3;

	animator = new Animator();

	TEXTURE_MGR.Load("graphics/additionals/door_01_normaldoor.png");
	ANI_CLIP_MGR.Load("animations/key_insert.csv");

	SetOrigin(Origins::BC);

	hitBox = new HitBox();
	key = new sf::Sprite();

	SpriteGo::Init();
}

void Door::Release()
{
	delete hitBox;
}

void Door::Reset()
{
	if(isLocked)
		doorClosedRightRect = { 84, 112, 25, 23 };

	SpriteGo::Reset();
	sprite.setTextureRect(doorTextureRect);

	doorOpened.setTexture(TEXTURE_MGR.Get(textureId), true);
	doorClosedLeft.setTexture(TEXTURE_MGR.Get(textureId), true);
	doorClosedRight.setTexture(TEXTURE_MGR.Get(textureId), true);

	doorOpened.setTextureRect(doorOpenedRect);
	doorClosedLeft.setTextureRect(doorClosedLeftRect);
	doorClosedRight.setTextureRect(doorClosedRightRect);

	SetOrigin(Origins::BC);
	if (type == MapType::Hidden)
	{
		sprite.setOrigin(GetOrigin() + sf::Vector2f(0.f, -10.f));
	}
	doorOpened.setOrigin({(float) doorOpened.getTextureRect().getSize().x * 0.5f, (float)doorOpened.getTextureRect().getSize().y + 2.f });
	doorClosedLeft.setOrigin({ (float)doorClosedLeft.getTextureRect().getSize().x * 0.5f, (float)doorClosedLeft.getTextureRect().getSize().y +2.f });
	doorClosedRight.setOrigin({ (float)doorClosedRight.getTextureRect().getSize().x * 0.5f, (float)doorClosedRight.getTextureRect().getSize().y +2.f });

	SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	SetScale({ 2.f,2.f });

	key->setTexture(TEXTURE_MGR.Get("graphics/additionals/door_01_normaldoor.png"), true);
	key->setTextureRect({ 105,167,15,22 });
	//key->setOrigin({ key->getLocalBounds().width * 0.5f + 5.f, 25.f});

	animator->SetTarget(key);
}

void Door::Update(float dt)
{
	sf::FloatRect bounds = doorOpened.getLocalBounds();
	if(isCleared)
	{
		bounds.height *= 0.3f;
	}
	hitBox->UpdateTransform(doorOpened, bounds);
	
	if (isStartKeyAnimation)
	{
		keyPlayingTime += dt;
		if (keyPlayingTime > keyPlayingTimeMax)
		{
			animator->Stop();
		}
	}

	if (!animator->IsPlaying() && isLocked && isStartKeyAnimation)
	{
		isLocked = false;
		isCleared = true;
		isStartKeyAnimation = false;
	}

	animator->Update(dt);
}

void Door::Draw(sf::RenderWindow& window)
{
	if (isCleared)
		window.draw(doorOpened);
	else
	{
		window.draw(doorClosedLeft);
		window.draw(doorClosedRight);
	}
	SpriteGo::Draw(window);
	hitBox->Draw(window);
	if (isStartKeyAnimation)
	{
		window.draw(*key);
	}
}

void Door::SetDoorDirection(int i)
{
	switch (i)
	{
	case 0:
		doorDirection = { 0.f, -1.f };
		break;
	case 1:
		doorDirection = { 1.f, 0.f };
		break;
	case 2:
		doorDirection = { 0.f, 1.f };
		break;
	case 3:
		doorDirection = { -1.f, 0.f };
		break;
	default:
		break;
	}
}

void Door::PlayUnlock()
{
	animator->Play("animations/key_insert.csv");
	isStartKeyAnimation = true;
}
