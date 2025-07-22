#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void Button::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 5;

	SetOrigin(Origins::MC);

	text = new TextGo("fonts/DS-DIGIT.TTF");
	text->SetOrigin(Origins::MC);

	rect = new sf::RectangleShape();

	SpriteGo::Init();
}

void Button::Release()
{
	SpriteGo::Release();
}

void Button::Reset()
{
	text->Reset();

	if(textureId != "")
		SpriteGo::Reset();

	text->SetPosition(position);
	if (textureId != "")
	{
		rect->setSize((sf::Vector2f)sprite.getTexture()->getSize());
	}
	rect->setPosition(position);

	originAlpha = rect->getFillColor().a;
	if (textureId != "")
	{
		originAlpha = sprite.getColor().a;
	}
}

void Button::Update(float dt)
{
	SpriteGo::Update(dt);

	if (SCENE_MGR.GetCurrentScene())
	{
		sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition());

		if (Utils::PointInTransformBounds(*rect, rect->getLocalBounds(), mousePos))
		{
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha * 0.5f));
			rect->setFillColor(sf::Color(rect->getFillColor().r, rect->getFillColor().g, rect->getFillColor().b, originAlpha * 0.5f));
			text->SetFillColor(sf::Color(text->GetText().getFillColor().r,
				text->GetText().getFillColor().g,
				text->GetText().getFillColor().b,
				originAlpha * 0.5f));
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				DoFunc();
			}
		}
		else
		{
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha));
			rect->setFillColor(sf::Color(rect->getFillColor().r, rect->getFillColor().g, rect->getFillColor().b, originAlpha));
			text->SetFillColor(sf::Color(text->GetText().getFillColor().r,
				text->GetText().getFillColor().g,
				text->GetText().getFillColor().b,
				originAlpha));
		}
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(*rect);
	text->Draw(window);
}

void Button::SetInitState()
{
	sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha));
	text->SetFillColor(sf::Color(text->GetText().getFillColor().r,
		text->GetText().getFillColor().g,
		text->GetText().getFillColor().b,
		originAlpha));
}

void Button::DoFunc()
{
	switch (type)
	{
	case Button::Type::Void:
		if (voidfunc)
		{
			voidfunc();
		}
		break;
	case Button::Type::buttonCount:
		break;
	default:
		break;
	}
	SetInitState();
}