#pragma once
#include "Scene.h"

class SpriteGo;
class Isaac;
class HitBox;

class SceneGame : public Scene
{
protected:
	std::vector<SpriteGo*> mapSprites;

	Isaac* isaac;

	sf::FloatRect currentMapSize;
	std::vector<HitBox*> boundary;

	sf::Vector2f offset = sf::Vector2f(140.f, 104.f);

public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void LoadStageField(const std::string& filePath);
	void CreateMatchedTypeGO(const std::string& filepath, const std::string& name);

	std::vector<SpriteGo*> GetMapSprites() { return mapSprites; }
	std::vector<HitBox*> GetMapBoundary() { return boundary; }
};

