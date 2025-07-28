#pragma once
#include "Scene.h"
#include "windows.h"
#include "commdlg.h"
#include "rapidcsv.h"
#include "Button.h"

class AnimationClip;
class Animator;
class AnimationFrame;
class SpriteGo;

class SceneAnimator : public Scene
{
protected:
	HWND hwnd;

	sf::RectangleShape body;
	sf::RectangleShape line;
	std::vector<AnimationFrame> animationFrames;
	std::vector<sf::RectangleShape> animationFrameBoxes;
	std::vector<sf::Vector2f> animationFrameBoxesInitPos;

	Button* saveAnimation = nullptr;
	Button* loadAnimation = nullptr;
	Button* loadFile = nullptr;

	AnimationClip* animation;

	std::vector<SpriteGo*> animationSprites;

	Animator* animator = nullptr;
	SpriteGo* animationBody = nullptr;

	bool isClipDrag = false;

	float beforeMousePosX;
	float afterMousePosX;

public:
	SceneAnimator();
	~SceneAnimator() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);

	rapidcsv::Document SaveAnimation();
	void SaveFile();
	void LoadField();
	void LoadFile(const std::string& fileName);
};

