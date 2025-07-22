#pragma once
#include "Scene.h"

class EditBoxUI;
class MapBoxUI;
class SpriteGo;

class SceneEditor :
    public Scene
{
protected:
	EditBoxUI* editBox = nullptr;
	MapBoxUI* mapBox = nullptr;

	SpriteGo* spriteChoosed = nullptr;
	sf::RectangleShape editBoxBody;
	std::list<SpriteGo*> backgroundSprites;

	bool isChoosed = false;

public:
	SceneEditor();
	~SceneEditor() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

