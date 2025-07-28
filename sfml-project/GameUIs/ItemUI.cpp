#include "stdafx.h"
#include "ItemUI.h"

ItemUI::ItemUI(const std::string& name)
	: GameObject(name)
{
}

void ItemUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
	coinImage.setPosition(pos + coinImagesPos[0]);
	bombImage.setPosition(pos + bombImagesPos[0]);
	keyImage.setPosition(pos + keyImagesPos[0]);
	for (int i = 0; i < 2; i++)
	{
		coinCountSprites[i]->setPosition(pos + coinImagesPos[i + 1]);
		bombCountSprites[i]->setPosition(pos + bombImagesPos[i + 1]);
		keyCountSprites[i]->setPosition(pos + keyImagesPos[i + 1]);
	}
}

void ItemUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void ItemUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
	coinImage.setScale(s);
	bombImage.setScale(s);
	keyImage.setScale(s);
	for(int i = 0; i<2; i++)
	{
		coinCountSprites[i]->setScale(s);
		bombCountSprites[i]->setScale(s);
		keyCountSprites[i]->setScale(s);
	}
}

void ItemUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void ItemUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void ItemUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	for (int i = 0; i < 10; i++)
	{
		fontImage.push_back("fonts/fontimage/" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < 2; i++)
	{
		coinCountSprites.push_back(new sf::Sprite());
		bombCountSprites.push_back(new sf::Sprite());
		keyCountSprites.push_back(new sf::Sprite());
	}
}

void ItemUI::Release()
{
}

void ItemUI::Reset()
{
	coinImage.setTexture(TEXTURE_MGR.Get("graphics/hudpickups.png"));
	coinImage.setTextureRect(coinRect);
	coinImage.setOrigin((sf::Vector2f)coinRect.getSize() * 0.5f);
	
	bombImage.setTexture(TEXTURE_MGR.Get("graphics/hudpickups.png"));
	bombImage.setTextureRect(bombRect);
	bombImage.setOrigin((sf::Vector2f)bombRect.getSize() * 0.5f);
	
	keyImage.setTexture(TEXTURE_MGR.Get("graphics/hudpickups.png"));
	keyImage.setTextureRect(keyRect);
	keyImage.setOrigin((sf::Vector2f)keyRect.getSize() * 0.5f);

	SetCoinCount(0);
	SetBombCount(0);
	SetKeyCount(0);

	sf::Vector2f countImageSize = (sf::Vector2f)coinCountSprites[0]->getTexture()->getSize();

	for (int i = 0; i < 3; i++)
	{
		coinImagesPos.push_back({ (i == 0 ? 0.f : countImageSize.x * 1.5f) + i * fontImageSize.x * 2.f, 0.f});
		bombImagesPos.push_back({ (i == 0 ? 0.f : countImageSize.x * 1.5f) + i * fontImageSize.x * 2.f, countImageSize.y * 2.5f });
		keyImagesPos.push_back({ (i == 0 ? 0.f : countImageSize.x * 1.5f) + i * fontImageSize.x * 2.f, countImageSize.y * 5.f });
	}

	SetPosition({ 60.f,120.f });
}

void ItemUI::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		SetCoinCount(GetCoinCount() + 1);
		SetBombCount(GetBombCount() + 1);
		SetKeyCount(GetKeyCount() + 1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num8))
	{
		SetCoinCount(GetCoinCount() - 1);
		SetBombCount(GetBombCount() - 1);
		SetKeyCount(GetKeyCount() - 1);
	}
}

void ItemUI::Draw(sf::RenderWindow& window)
{
	window.draw(coinImage);
	window.draw(bombImage);
	window.draw(keyImage);
	for (int i = 0; i < 2; i++)
	{
		window.draw(*coinCountSprites[i]);
		window.draw(*bombCountSprites[i]);
		window.draw(*keyCountSprites[i]);
	}
}

void ItemUI::SetCoinCount(int count)
{
	coinCount = Utils::Clamp(count, 0, 99);
	for (int i = 0; i < 2; i++)
	{
		int eachCoinCount = i == 0 ? coinCount / 10 : coinCount % 10;

		coinCountSprites[i]->setTexture(TEXTURE_MGR.Get("fonts/fontimage/" + std::to_string(eachCoinCount) + ".png"), true);
		coinCountSprites[i]->setOrigin((sf::Vector2f)coinRect.getSize() * 0.5f);
	}
}

void ItemUI::SetBombCount(int count)
{
	bombCount = Utils::Clamp(count, 0, 99);
	for (int i = 0; i < 2; i++)
	{
		int eachBombCount = i == 0 ? bombCount / 10 : bombCount % 10;

		bombCountSprites[i]->setTexture(TEXTURE_MGR.Get("fonts/fontimage/" + std::to_string(eachBombCount) + ".png"), true);
		bombCountSprites[i]->setOrigin((sf::Vector2f)coinRect.getSize() * 0.5f);
	}
}

void ItemUI::SetKeyCount(int count)
{
	keyCount = Utils::Clamp(count, 0, 99);
	for (int i = 0; i < 2; i++)
	{
		int eachKeyCount = i == 0 ? keyCount / 10 : keyCount % 10;

		keyCountSprites[i]->setTexture(TEXTURE_MGR.Get("fonts/fontimage/" + std::to_string(eachKeyCount) + ".png"), true);
		keyCountSprites[i]->setOrigin((sf::Vector2f)coinRect.getSize() * 0.5f);
	}
}

void ItemUI::SetItemUICount(Items id, int c)
{
	switch (id)
	{
	case Items::Coin:
		SetCoinCount(c);
		break;
	case Items::Bomb:
		SetBombCount(c);
		break;
	case Items::Key:
		SetKeyCount(c);
		break;
	default:
		break;
	}
}

int ItemUI::GetItemUICount(Items id) const
{
	switch (id)
	{
	case Items::Coin:
		return GetCoinCount();
	case Items::Bomb:
		return GetBombCount();
	case Items::Key:
		return GetKeyCount();
	default:
		break;
	}
	return 0;
}
