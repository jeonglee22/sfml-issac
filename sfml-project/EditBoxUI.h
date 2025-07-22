#pragma once
#include "GameObject.h"
#include "Button.h"

class Scene;
class SpriteGo;

class EditBoxUI : public GameObject
{
protected:
	sf::RectangleShape body;

	sf::RectangleShape pickBox;
	SpriteGo* pickedSprite;

	std::vector<Button*> typeButtons;
	std::vector<Button*> styleTypeButtons;
	std::vector<Button*> obstacleTypeButtons;
	std::vector<Button*> enemyTypeButtons;
	std::vector<std::string> filenames;

	Scene* scene;

	sf::Vector2f typeButtonPos;

	std::string basementGroundId;
	std::string sheolGroundId;
	std::string depthsGroundId;
	std::string cavesGroundId;
	std::vector<SpriteGo*> basementGround;



	sf::Vector2f gridSize = { 60.f,60.f };

	bool isPicked = false;

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

	void InitStyleTypeButtons();
	void InitObstacleTypeButtons();
	void InitEnemyTypeButtons();
	void ResetStyleTypeButtons(float yPos = -450.f);
	void ResetObstacleTypeButtons();
	void ResetEnemyTypeButtons();

	void LoadBackGround(const std::string& filePath);

	std::vector<SpriteGo*> GetActiveSprites() { return basementGround; }
	sf::RectangleShape GetMainUIBody() { return body; }

	SpriteGo* SetChoosedSprite(SpriteGo* sp);
	void SetOffChoosedSprite();

	void DisableAllButtons();
};

