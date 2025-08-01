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
		textureId = "graphics/additionals/door_01_normaldoor.png";
		doorTextureRect = { 8, 9, 49, 33 };
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
}

void Door::SetRotation(float rot)
{
	SpriteGo::SetRotation(rot);
	doorOpened.setRotation(rot);
	doorClosedLeft.setRotation(rot);
	doorClosedRight.setRotation(rot);
}

void Door::SetScale(const sf::Vector2f& s)
{
	SpriteGo::SetScale(s);
	doorOpened.setScale(s);
	doorClosedLeft.setScale(s);
	doorClosedRight.setScale(s);
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
}

void Door::SetOrigin(Origins preset)
{
	SpriteGo::SetOrigin(preset);
}

void Door::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 3;

	SetOrigin(Origins::BC);

	hitBox = new HitBox();

	SpriteGo::Init();
}

void Door::Release()
{
	delete hitBox;
}

void Door::Reset()
{
	SpriteGo::Reset();
	sprite.setTextureRect(doorTextureRect);

	doorOpened.setTexture(TEXTURE_MGR.Get(textureId), true);
	doorClosedLeft.setTexture(TEXTURE_MGR.Get(textureId), true);
	doorClosedRight.setTexture(TEXTURE_MGR.Get(textureId), true);

	doorOpened.setTextureRect(doorOpenedRect);
	doorClosedLeft.setTextureRect(doorClosedLeftRect);
	doorClosedRight.setTextureRect(doorClosedRightRect);

	SetOrigin(Origins::BC);
	doorOpened.setOrigin({(float) doorOpened.getTextureRect().getSize().x * 0.5f, (float)doorOpened.getTextureRect().getSize().y + 2.f });
	doorClosedLeft.setOrigin({ (float)doorClosedLeft.getTextureRect().getSize().x * 0.5f, (float)doorClosedLeft.getTextureRect().getSize().y +2.f });
	doorClosedRight.setOrigin({ (float)doorClosedRight.getTextureRect().getSize().x * 0.5f, (float)doorClosedRight.getTextureRect().getSize().y +2.f });

	SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	SetScale({ 2.f,2.f });
}

void Door::Update(float dt)
{
	sf::FloatRect bounds = doorOpened.getLocalBounds();
	if(isCleared)
	{
		bounds.height *= 0.3f;
	}
	hitBox->UpdateTransform(doorOpened, bounds);
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
