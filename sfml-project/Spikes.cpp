#include "stdafx.h"
#include "Spikes.h"

Spikes::Spikes(const std::string& texId, const std::string& name)
	: Obstacles(texId, name)
{
}

void Spikes::Init()
{
	Obstacles::Init();
}

void Spikes::Release()
{
	Obstacles::Release();
}

void Spikes::Reset()
{
	Obstacles::Reset();
}

void Spikes::Update(float dt)
{
	Obstacles::Update(dt);
}

void Spikes::Draw(sf::RenderWindow& window)
{
	Obstacles::Draw(window);
}
