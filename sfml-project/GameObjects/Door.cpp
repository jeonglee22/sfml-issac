#include "stdafx.h"
#include "Door.h"

Door::Door(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
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
	sprite.setTextureRect({ 8, 9, 49, 33 });

	doorOpened.setTexture(TEXTURE_MGR.Get(textureId), true);
	doorClosedLeft.setTexture(TEXTURE_MGR.Get(textureId), true);
	doorClosedRight.setTexture(TEXTURE_MGR.Get(textureId), true);

	doorOpened.setTextureRect({ 84,16,25,23 });
	doorClosedLeft.setTextureRect({ 19,64,14,23 });
	doorClosedRight.setTextureRect({ 96,64,14,23 });

	SetOrigin(Origins::BC);
	doorOpened.setOrigin({(float) doorOpened.getTextureRect().getSize().x * 0.5f, (float)doorOpened.getTextureRect().getSize().y + 2.f });
	doorClosedLeft.setOrigin({ (float)doorClosedLeft.getTextureRect().getSize().x, (float)doorClosedLeft.getTextureRect().getSize().y +2.f });
	doorClosedRight.setOrigin({ 0.f, (float)doorClosedRight.getTextureRect().getSize().y +2.f });

	SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	SetScale({ 2.f,2.f });
}

void Door::Update(float dt)
{
	hitBox->UpdateTransform(doorOpened, doorOpened.getLocalBounds());
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