#include "stdafx.h"
#include "PauseUI.h"
#include "SceneGame.h"

PauseUI::PauseUI(const std::string& textureId, const std::string& name)
	: GameObject(name), texId(textureId)
{
}

void PauseUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void PauseUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void PauseUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void PauseUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void PauseUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void PauseUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 20;

	blackBack.setFillColor(sf::Color(0, 0, 0, 150));
	blackBack.setSize(FRAMEWORK.GetWindowSizeF());
}

void PauseUI::Release()
{
}

void PauseUI::Reset()
{
	pos = 0;

	body.setTexture(TEXTURE_MGR.Get(texId));
	body.setTextureRect(bodyRect);
	body.setOrigin((sf::Vector2f)bodyRect.getSize() * 0.5f);
	body.setScale({ 2.f,2.f });
	body.setPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

	pointer.setTexture(TEXTURE_MGR.Get(texId));
	pointer.setTextureRect(pointerRect);
	pointer.setOrigin((sf::Vector2f)pointerRect.getSize() * 0.5f);
	pointer.setScale({ 2.f,2.f });
	pointer.setPosition(pointerPos[pos]);

	SetActive(false);
}

void PauseUI::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Up) || InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		pos = (pos + 1) % 2;
		pointer.setPosition(pointerPos[pos]);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetActive(false);
		FRAMEWORK.SetTimeScale(1.f);
		if (pos == 0)
		{
			if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Stage)
				((SceneGame*)SCENE_MGR.GetCurrentScene())->SetGameStop(false);
		}
		else
		{
			isRestart = true;
		}
	}
}

void PauseUI::Draw(sf::RenderWindow& window)
{
	window.draw(blackBack);
	window.draw(body);
	window.draw(pointer);
}
