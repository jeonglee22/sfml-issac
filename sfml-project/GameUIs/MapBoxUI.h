#pragma once
#include "GameObject.h"

class SceneEditor;

class MapBoxUI : public GameObject
{
public:
	enum class Mode
	{
		None = -1,
		Background,
		obstacles,
		enemies,
		additionals,
	};

protected:
	sf::RectangleShape body;
	std::vector<sf::RectangleShape> obstacleGrid;
	std::vector<sf::RectangleShape> backgroundGrid;
	std::vector<sf::RectangleShape> enemyGrid;

	SceneEditor* editorScene = nullptr;

	int backgroundGridXcount = 8;
	int backgroundGridYcount = 10;
	int obstacleGridXcount = 8;
	int obstacleGridYcount = 14;
	
	sf::Vector2f backgroundGridSize = { 104.f,104.f };
	sf::Vector2f obstacleGridSize = { 52.f,52.f };
	sf::Vector2f topLeft = { 560.f - obstacleGridSize.x * 6.5f, 540.f - obstacleGridSize.y * 3.5f };

	std::vector<sf::FloatRect> obstacleGridRect;
	std::vector<sf::FloatRect> enemyGridRect;
	std::vector<sf::FloatRect> backgroundGridRect;

	bool isCheckingMap = false;
	Mode currentType = Mode::None;

public:
	MapBoxUI(const std::string& name = "");
	virtual ~MapBoxUI() = default;

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

	void SetGridRectValue();
	sf::RectangleShape GetRectHavePoint(const sf::Vector2f& point);
	sf::Vector2f GetObstacleGridSize() { return obstacleGridSize; }
	sf::Vector2f GetBackGroundGridSize() { return backgroundGridSize; }
	sf::Vector2f GetTopLeft() { return topLeft; }
	bool GetCheckingMap() { return isCheckingMap; }
	std::vector<sf::RectangleShape> GetMapGird();
	std::vector<sf::FloatRect> GetMapRect();
};

