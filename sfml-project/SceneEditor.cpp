#include "stdafx.h"
#include "SceneEditor.h"
#include "EditBoxUI.h"
#include "MapBoxUI.h"

SceneEditor::SceneEditor()
	: Scene(SceneIds::Editor)
{
}

void SceneEditor::Init()
{
	texIds.push_back("graphics/basement/01_basement.png");

	fontIds.push_back("fonts/DS-DIGIT.TTF");

	editBox = (EditBoxUI*)AddGameObject(new EditBoxUI());
	mapBox = (MapBoxUI*)AddGameObject(new MapBoxUI());

	Scene::Init();
}

void SceneEditor::Enter()
{
	FRAMEWORK.GetWindow().setSize({ 1920,1080 });
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	isChoosed = false;

	Scene::Enter();
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isChoosed)
	{
		std::vector<sf::Sprite> sprites = editBox->GetActiveSprites();
		auto mousePos = Scene::ScreenToUi(InputMgr::GetMousePosition());
		for (auto sprite : sprites)
		{
			if (Utils::PointInTransformBounds(sprite, sprite.getLocalBounds(), mousePos))
			{
				spriteChoosed = sf::Sprite(sprite);
				isChoosed = true;
			}
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isChoosed)
	{
		auto mousePos = Scene::ScreenToUi(InputMgr::GetMousePosition());
		spriteChoosed.setPosition(mousePos);
		std::cout << "sprite" << std::endl;
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isChoosed)
	{

	}
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(spriteChoosed);
}