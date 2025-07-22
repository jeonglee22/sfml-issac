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

public:
	SceneEditor();
	~SceneEditor() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

