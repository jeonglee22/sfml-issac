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

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;

	SpriteGo::Init();
}

void Obstacles::Release()
{
	delete hitBox;

	SpriteGo::Release();
}

void Obstacles::Reset()
{
	SpriteGo::Reset();
}

void Obstacles::Update(float dt)
{
	hitBox->UpdateTransform(sprite, GetLocalBounds());
}

void Obstacles::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	hitBox->Draw(window);
}