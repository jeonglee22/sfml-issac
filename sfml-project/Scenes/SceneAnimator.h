#pragma once
#include "Scene.h"
#include "windows.h"
#include "commdlg.h"
#include "rapidcsv.h"
#include "Button.h"
#include "AnimationClip.h"
#include "Animator.h"

class AnimationClip;
class Animator;
class AnimationFrame;
class SpriteGo;

class SceneAnimator : public Scene
{
protected:
	HWND hwnd;

	sf::RectangleShape body;
	sf::RectangleShape blackBody;
	sf::RectangleShape line;
	sf::RectangleShape spritePickRect;
	sf::RectangleShape spriteSheetOutline;

	std::string spriteSheetName;
	TextGo* fps;
	SpriteGo* background;

	std::vector<AnimationFrame> animationFrames;
	std::vector<sf::RectangleShape> animationFrameBoxes;
	std::vector<sf::Vector2f> animationFrameBoxesInitPos;

	Button* saveAnimation = nullptr;
	Button* loadAnimation = nullptr;
	Button* loadFile = nullptr;
	Button* clearAnimation = nullptr;

	AnimationClip animation;

	std::vector<SpriteGo*> animationSprites;

	Animator animator;
	SpriteGo* animationBody = nullptr;
	SpriteGo* spriteField = nullptr;

	Origins frameOrigin = Origins::MC;


	bool isClipDrag = false;
	bool isSpritePick = false;
	bool isLoading = false;

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
	void LoadFile(bool isAnimation);
	void LoadAnimationFile(const std::string& fileName);
	void LoadSpriteFile(const std::string& fileName);

	void PlaySpritesFromLoad();

	void MoveAnimationClip();
	void PickSpriteRect();
	sf::IntRect ConvertToSpriteSheetPos();

	void ClearAnimationBox();

	void AddPickSprite();
	void RemoveSpriteInFrames();
	void AddEachAnimationSpriteFrame(AnimationFrame frame);

	void SetAnimationLoopType(AnimationLoopTypes ty) { animation.loopType = ty; }
	void SetAnimationFPS(int fps) { animation.fps = fps; }
	void SetAnimationId(const std::string& str) { animation.id = str; }
};

