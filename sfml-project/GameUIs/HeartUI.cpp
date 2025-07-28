#include "stdafx.h"
#include "HeartUI.h"

HeartUI::HeartUI(const std::string& textureId, const std::string& name)
	: texId(textureId), GameObject(name)
{
}

void HeartUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
	for (int i = 0; i < (maxHPCount + 1) / 2; i++)
		hearts[i]->setPosition(pos + (float) i * seperatePos *2.f);
}

void HeartUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void HeartUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
	for (int i = 0; i < (maxHPCount + 1) / 2; i++)
		hearts[i]->setScale(s);
}

void HeartUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void HeartUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void HeartUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	for (int i = 0; i < (maxHPCount + 1) / 2; i++)
	{
		hearts.push_back(new sf::Sprite());
	}
}

void HeartUI::Release()
{
}

void HeartUI::Reset()
{
	for (int i = 0; i < (maxHPCount + 1) / 2; i++)
	{
		hearts[i]->setTexture(TEXTURE_MGR.Get(texId), true);
		hearts[i]->setTextureRect(fullHeart);
		hearts[i]->setOrigin((sf::Vector2f)fullHeart.getSize() * 0.5f);
	}

	SetPosition({ 150.f, 60.f });
}

void HeartUI::Update(float dt)
{
	if (beforeMaxHPCount != maxHPCount)
	{
		for (int i = 0; i < (maxHPCount - beforeMaxHPCount) / 2; i++)
		{
			hearts.push_back(new sf::Sprite());
		}
		for (int i = 0; i < (maxHPCount - beforeMaxHPCount) / 2; i++)
		{
			hearts[i + (maxHPCount + 1) / 2]->setTexture(TEXTURE_MGR.Get(texId), true);
			hearts[i + (maxHPCount + 1) / 2]->setTextureRect(emptyHeart);
			hearts[i + (maxHPCount + 1) / 2]->setOrigin((sf::Vector2f)emptyHeart.getSize() * 0.5f);
		}
		beforeMaxHPCount = maxHPCount;
	}
	if(beforeHPCount != currentHPCount)
	{
		if (currentHPCount > beforeHPCount)
		{
			int changePosStart = beforeHPCount / 2;
			int changePosEnd = (currentHPCount + 1) / 2;

			for (int i = changePosStart; i < changePosEnd; i++)
			{
				if (i == changePosEnd - 1 && currentHPCount % 2 == 1)
				{
					hearts[i]->setTexture(TEXTURE_MGR.Get(texId), true);
					hearts[i]->setTextureRect(halfHeart);
					hearts[i]->setOrigin((sf::Vector2f)halfHeart.getSize() * 0.5f);
				}
				else
				{
					hearts[i]->setTexture(TEXTURE_MGR.Get(texId), true);
					hearts[i]->setTextureRect(fullHeart);
					hearts[i]->setOrigin((sf::Vector2f)fullHeart.getSize() * 0.5f);
				}
			}
		}
		else
		{
			int changePosStart = currentHPCount / 2;
			int changePosEnd = (beforeHPCount + 1) / 2;

			for (int i = changePosStart; i < changePosEnd; i++)
			{
				if (i == changePosStart && currentHPCount % 2 == 1)
				{
					hearts[i]->setTexture(TEXTURE_MGR.Get(texId), true);
					hearts[i]->setTextureRect(halfHeart);
					hearts[i]->setOrigin((sf::Vector2f)halfHeart.getSize() * 0.5f);
				}
				else
				{
					hearts[i]->setTexture(TEXTURE_MGR.Get(texId), true);
					hearts[i]->setTextureRect(emptyHeart);
					hearts[i]->setOrigin((sf::Vector2f)emptyHeart.getSize() * 0.5f);
				}
			}
		}
		beforeHPCount = currentHPCount;
	}
}

void HeartUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	for (auto heart : hearts)
		window.draw(*heart);
}