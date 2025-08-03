#include "stdafx.h"
#include "ExplainUI.h"
#include "TextGo.h"

ExplainUI::ExplainUI(const std::string& textureId, const std::string& name)
	: GameObject(name), texId(textureId)
{
}

void ExplainUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
	comment->SetPosition(pos + sf::Vector2f(0.f, -25.f));
	explain->SetPosition(pos + sf::Vector2f(0.f, 35.f));
}

void ExplainUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void ExplainUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void ExplainUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void ExplainUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void ExplainUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 10;

	SetOrigin(Origins::MC);

	comment = new TextGo(commentId, "comment");
	comment->SetCharacterSize(40);
	comment->SetOrigin(Origins::MC);
	comment->Init();

	explain = new TextGo(explainId, "explain");
	explain->SetCharacterSize(15);
	explain->SetOrigin(Origins::MC);
	explain->Init();
	explain->GetText().setOutlineColor(sf::Color::Black);
	explain->GetText().setOutlineThickness(2.f);
}

void ExplainUI::Release()
{
	delete comment;
	delete explain;
}

void ExplainUI::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texId));
	Utils::SetOrigin(body, originPreset);
	body.setScale({ 2.f,2.f });

	comment->Reset();
	explain->Reset();

	SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

	comment->SetString("The Sad Onion");
	explain->SetString("Tears up");

	SetActive(false);
}

void ExplainUI::Update(float dt)
{
}

void ExplainUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	comment->Draw(window);
	if(explain->GetActive())
	{
		explain->Draw(window);
	}
}