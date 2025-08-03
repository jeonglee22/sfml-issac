#pragma once
#include "GameObject.h"
#include "TextGo.h"

class ExplainUI : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId;

	TextGo* comment;
	TextGo* explain;
	std::string commentId = "fonts/upheavtt.ttf";
	//std::string explainId = "fonts/pf_tempesta_seven_condensed.ttf";
	std::string explainId = "fonts/pf_tempesta_seven_condensed_bold.ttf";

public:
	ExplainUI(const std::string& textureId = "", const std::string & name = "");
	virtual ~ExplainUI() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetComment(const std::string& text) { comment->SetString(text); }
	void SetExplain(const std::string& text) { explain->SetString(text); }
	void SetActiveComment(bool b) { comment->SetActive(b); }
	void SetActiveExplain(bool b) { explain->SetActive(b); }
};

