#include "stdafx.h"
#include "GameOverUI.h"

GameOverUI::GameOverUI(const std::string& name)
	: GameObject(name)
{
}

void GameOverUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void GameOverUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void GameOverUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void GameOverUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void GameOverUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void GameOverUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 20;

	blackBack.setFillColor(sf::Color(0, 0, 0, 150));
	blackBack.setSize(FRAMEWORK.GetWindowSizeF());
}

void GameOverUI::Release()
{
}

void GameOverUI::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	body.setTextureRect(bodyRect);
	body.setOrigin((sf::Vector2f)bodyRect.getSize() * 0.5f);
	body.setScale({ 2.f,2.f });
	body.setPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

	exitWidget.setTexture(TEXTURE_MGR.Get(widgetId));
	exitWidget.setTextureRect(widgetRect[0]);
	exitWidget.setOrigin({ 0.f,(float)widgetRect[0].getSize().y });
	exitWidget.setScale({ 2.f,2.f });
	exitWidget.setPosition(sf::Vector2f(0.f, FRAMEWORK.GetWindowSizeF().y) + sf::Vector2f(0, 20.f));

	exitText.setTexture(TEXTURE_MGR.Get(exitId));
	exitText.setOrigin({ 0.f,exitText.getLocalBounds().getSize().y});
	exitText.setScale({ 0.5f,0.5f });
	exitText.setPosition(sf::Vector2f(0.f, FRAMEWORK.GetWindowSizeF().y) + sf::Vector2f(40.f, -30.f));

	restartWidget.setTexture(TEXTURE_MGR.Get(widgetId));
	restartWidget.setTextureRect(widgetRect[1]);
	restartWidget.setOrigin((sf::Vector2f)widgetRect[1].getSize());
	restartWidget.setScale({ 2.f,2.f });
	restartWidget.setPosition(FRAMEWORK.GetWindowSizeF() + sf::Vector2f(30.f, 60.f));

	restartText.setTexture(TEXTURE_MGR.Get(restartId));
	restartText.setOrigin(restartText.getLocalBounds().getSize());
	restartText.setScale({ 0.5f,0.5f });
	restartText.setPosition(FRAMEWORK.GetWindowSizeF() + sf::Vector2f(-30.f,-30.f));

	SetActive(false);
}

void GameOverUI::Update(float dt)
{
	SetActive(false);
	if (InputMgr::GetKey(sf::Keyboard::H))
		SetActive(true);
}

void GameOverUI::Draw(sf::RenderWindow& window)
{
	window.draw(blackBack);
	window.draw(body);
	window.draw(exitWidget);
	window.draw(exitText);
	window.draw(restartWidget);
	window.draw(restartText);
}