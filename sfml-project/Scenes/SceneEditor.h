#pragma once
#include "Scene.h"
#include "rapidcsv.h"

class EditBoxUI;
class MapBoxUI;
class SpriteGo;
class Button;
class HitBox;

class SceneEditor :
    public Scene
{
protected:
	EditBoxUI* editBox = nullptr;
	MapBoxUI* mapBox = nullptr;

	Button* save = nullptr;
	Button* load = nullptr;

	SpriteGo* spriteChoosed = nullptr;
	sf::RectangleShape editBoxBody;
	std::list<SpriteGo*> mapSprites;

	bool isChoosed = false;
	bool isSetDrop = false;

public:
	SceneEditor();
	~SceneEditor() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	rapidcsv::Document SaveFile();
	void SaveField();
	void LoadField();
	void LoadFile(const std::string& fileName);

	SpriteGo* CheckAlreadySetGrid(const SpriteGo* sp);
	SpriteGo* CheckAlreadySetGrid();
	bool IsNotOnGrid();

	std::string GetCurrentType() const;
};

