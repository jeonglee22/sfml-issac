#pragma once
#include "Scene.h"
#include "windows.h"
#include "commdlg.h"
#include "rapidcsv.h"
#include "Button.h"

class AnimationClip;
class Animator;

class SceneAnimator : public Scene
{
protected:
	HWND hwnd;

	Button* saveAnimation = nullptr;
	Button* loadAnimation = nullptr;
	Button* loadFile = nullptr;

	AnimationClip* animation = nullptr;

	std::vector<sf::Sprite*> animationSprites;

	Animator* animator = nullptr;
	sf::Sprite* animationBody = nullptr;

public:
	SceneAnimator();
	~SceneAnimator() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;

	rapidcsv::Document SaveAnimation();
	void SaveFile();
	void LoadField();
	void LoadFile(const std::string& fileName);
};

