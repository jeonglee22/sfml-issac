#pragma once
#include "Scene.h"

class EditBoxUI;
class MapBoxUI;

class SceneEditor :
    public Scene
{
protected:
	EditBoxUI* editBox;
	MapBoxUI* mapBox;

	sf::Sprite spriteChoosed;

	bool isChoosed = false;

public:
	SceneEditor();
	~SceneEditor() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

