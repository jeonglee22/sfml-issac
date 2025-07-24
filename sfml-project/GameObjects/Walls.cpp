#include "stdafx.h"
#include "Walls.h"
#include "HitBox.h"

Walls::Walls(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void Walls::Init()
{
	hitBox = new HitBox();

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;

	SpriteGo::Init();
}

void Walls::Release()
{
	delete hitBox;

	SpriteGo::Release();
}

void Walls::Reset()
{
	SpriteGo::Reset();
}

void Walls::Update(float dt)
{
	hitBox->UpdateTransform(sprite, GetLocalBounds());
}

void Walls::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	hitBox->Draw(window);
}