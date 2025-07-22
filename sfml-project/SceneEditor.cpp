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

	auto mousePos = Scene::ScreenToUi(InputMgr::GetMousePosition());
	editBoxBody = editBox->GetMainUIBody();
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && 
		Utils::PointInTransformBounds(editBoxBody, editBoxBody.getLocalBounds(), mousePos))
	{
		std::vector<SpriteGo*> sprites = editBox->GetActiveSprites();
		for (auto sprite : sprites)
		{
			if (Utils::PointInTransformBounds(sprite->GetSprite(), sprite->GetSprite().getLocalBounds(), mousePos))
			{
				isChoosed = true;
				spriteChoosed = editBox->SetChoosedSprite(sprite);
			}
		}
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && isChoosed)
	{
		sf::Vector2f boxPos = mapBox->GetRectCenterHavePoint(mousePos);
		if (boxPos != sf::Vector2f(0.f,0.f))
		{
			SpriteGo* sprite = new SpriteGo(*spriteChoosed);
			sprite->SetOrigin(Origins::MC);
			sprite->SetPosition(boxPos);
			backgroundSprites.push_back(sprite);
		}
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && 
		Utils::PointInTransformBounds(editBoxBody, editBoxBody.getLocalBounds(), mousePos))
	{
		isChoosed = false;
		editBox->SetOffChoosedSprite();
		spriteChoosed = nullptr;
	}
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	for (auto sprite : backgroundSprites)
	{
		sprite->Draw(window);
	}
}