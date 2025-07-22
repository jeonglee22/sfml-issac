#pragma once
#include "GameObject.h"
#include "Button.h"

class Scene;

class EditBoxUI : public GameObject
{
protected:
	sf::RectangleShape body;
	std::vector<Button*> typeButtons;
	Scene* scene;

	sf::Vector2f typeButtonPos;

	std::string basementGroundId;
	std::vector<sf::Sprite> basementGround;

	sf::Vector2f gridSize = { 60.f,60.f };

public:
	EditBoxUI(const std::string& name = "");
	virtual ~EditBoxUI() = default;

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

	void LoadBackGround(const std::string& filePath);
};

