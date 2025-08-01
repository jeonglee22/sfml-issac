#include "stdafx.h"
#include "Obstacles.h"
#include "HitBox.h"

Obstacles::Obstacles(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void Obstacles::Init()
{
	hitBox = new HitBox();
	//tearHitBox = new HitBox();

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;

	SpriteGo::Init();
}

void Obstacles::Release()
{
	delete hitBox;
	//delete tearHitBox;

	SpriteGo::Release();
}

void Obstacles::Reset()
{
	SpriteGo::Reset();
}

void Obstacles::Update(float dt)
{
	hitBox->UpdateTransform(sprite, GetLocalBounds());

	/*tearHitBox->UpdateTransform(sprite, GetLocalBounds());
	sf::Vector2f spriteSize = sprite.getLocalBounds().getSize();
	tearHitBox->rect.setPosition(position + sf::Vector2f( spriteSize.x, 0.f ));
	tearHitBox->rect.setSize({ spriteSize.x * 0.1f, spriteSize.y * 0.3f});
	tearHitBox->rect.setOrigin({ tearHitBox->rect.getSize().x * 0.5f, 0.f });*/
}

void Obstacles::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	hitBox->Draw(window);
	//tearHitBox->Draw(window);
}