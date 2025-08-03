#include "stdafx.h"
#include "BossMapEnterUI.h"

BossMapEnterUI::BossMapEnterUI(const std::string& name)
	: GameObject(name)
{
}

void BossMapEnterUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void BossMapEnterUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void BossMapEnterUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void BossMapEnterUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void BossMapEnterUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void BossMapEnterUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 30;
}

void BossMapEnterUI::Release()
{
}

void BossMapEnterUI::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	body.setScale({ 10.f,10.f });

	playerName.setTexture(TEXTURE_MGR.Get(nameId));
	playerName.setTextureRect(playerNameRect);
	playerName.setOrigin((sf::Vector2f)playerNameRect.getSize() * 0.5f);
	playerName.setScale({ 2.f,2.f });
	playerName.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f - 250.f, 80.f });

	playerSprite.setTexture(TEXTURE_MGR.Get(playerSpriteId));
	playerSprite.setOrigin(playerSprite.getLocalBounds().getSize() * 0.5f);
	playerSprite.setScale({ 2.f,2.f });
	playerSprite.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f - 250.f, 350.f });

	playerPlate.setTexture(TEXTURE_MGR.Get(playerPlateId));
	playerPlate.setOrigin(playerPlate.getLocalBounds().getSize() * 0.5f);
	playerPlate.setScale({ 2.f,2.f });
	playerPlate.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f - 250.f, 400.f });

	bossName.setTexture(TEXTURE_MGR.Get(nameId));
	bossName.setTextureRect(bossNameRect["Dingle"]);
	bossName.setOrigin((sf::Vector2f)bossNameRect["Dingle"].getSize() * 0.5f);
	bossName.setScale({ 2.f,2.f });
	bossName.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f + 250.f, 80.f });

	bossSprite.setTexture(TEXTURE_MGR.Get(bossSpriteId["Dingle"]));
	bossSprite.setOrigin(bossSprite.getLocalBounds().getSize() * 0.5f);
	bossSprite.setScale({ 2.f,2.f });
	bossSprite.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f + 250.f, 300.f });

	bossPlate.setTexture(TEXTURE_MGR.Get(bossPlateId));
	bossPlate.setOrigin(bossPlate.getLocalBounds().getSize() * 0.5f);
	bossPlate.setScale({ 2.f,2.f });
	bossPlate.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f + 250.f, 400.f });

	vsSprite.setTexture(TEXTURE_MGR.Get(nameId));
	vsSprite.setTextureRect(vsRect);
	vsSprite.setOrigin((sf::Vector2f)vsRect.getSize() * 0.5f);
	vsSprite.setScale({ 2.f,2.f });
	vsSprite.setPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 80.f });

	SetActive(false);
}

void BossMapEnterUI::Update(float dt)
{

	bossName.setTextureRect(bossNameRect[pickedBoss]);
	bossName.setOrigin((sf::Vector2f)bossNameRect[pickedBoss].getSize() * 0.5f);

	bossSprite.setTexture(TEXTURE_MGR.Get(bossSpriteId[pickedBoss]));
	bossSprite.setOrigin(bossSprite.getLocalBounds().getSize() * 0.5f);
}

void BossMapEnterUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(playerName);
	window.draw(vsSprite);
	window.draw(bossName);
	window.draw(playerPlate);
	window.draw(bossPlate);
	window.draw(playerSprite);
	window.draw(bossSprite);
}