#pragma once
#include "SpriteGo.h"
#include "TextGo.h"

class Button : public SpriteGo
{
public:
	enum class Type
	{
		None = -1,
		Void,

		buttonCount,
	};
protected:
	std::function<void()> voidfunc;

	TextGo* text = nullptr;
	sf::RectangleShape* rect = nullptr;

	bool isClicked = false;

	Type type;

	sf::Uint8 originAlpha;

public:
	Button(const std::string& texId = "", const std::string& name = "");
	virtual ~Button() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetTextColor(const sf::Color& c) { text->SetFillColor(c); }
	void SetTextSize(int i) { text->SetCharacterSize(i); }
	void SetTextString(const std::string& str) { text->SetString(str); }
	void SetTextPosition(const sf::Vector2f& pos) { text->SetPosition(this->GetPosition() + pos); }
	void SetTextOrigin(const sf::Vector2f& o) { text->SetOrigin(o); }
	void SetTextOrigin(const Origins o) { text->SetOrigin(o); }

	void SetButtonRectSize(const sf::Vector2f& size) { rect->setSize(size); }
	void SetButtonRectColor(const sf::Color& c) { rect->setFillColor(c); }
	void SetButtonRectOutlineColor(const sf::Color& c) { rect->setOutlineColor(c); }
	void SetButtonRectOutlineThickness(float t) { rect->setOutlineThickness(t); }
	void SetButtonRectPosition(const sf::Vector2f& pos) { rect->setPosition(this->GetPosition() + pos); }
	void SetButtonRectOrigin(const sf::Vector2f& o) { rect->setOrigin(o); }

	void SetInitState();

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }

	void SetButtonFunc(const std::function<void()>& func)
	{
		voidfunc = func;
		type = Type::Void;
	}
	void DoFunc();
};

