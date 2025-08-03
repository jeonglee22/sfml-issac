#include "stdafx.h"
#include "SceneStart.h"
#include "SpriteGo.h"

SceneStart::SceneStart()
	: Scene(SceneIds::Start)
{
}

void SceneStart::Init()
{
	texIds.push_back("graphics/mainmenu/titlemenu.png");
	texIds.push_back("graphics/mainmenu/menushadow.png");
	texIds.push_back("graphics/mainmenu/menuoverlay.png");

	soundIds.push_back("sounds/book page turn.wav");

	background = (SpriteGo*)AddGameObject(new SpriteGo("graphics/mainmenu/titlemenu.png"));
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

	logo = (SpriteGo*)AddGameObject(new SpriteGo("graphics/mainmenu/titlemenu.png"));
	logo->sortingLayer = SortingLayers::Background;
	logo->sortingOrder = 2;

	pressStart = (SpriteGo*)AddGameObject(new SpriteGo("graphics/mainmenu/titlemenu.png"));
	pressStart->sortingLayer = SortingLayers::Background;
	pressStart->sortingOrder = 1;

	shading = (SpriteGo*)AddGameObject(new SpriteGo("graphics/mainmenu/menushadow.png"));
	shading->sortingLayer = SortingLayers::Background;
	shading->sortingOrder = 3;

	overlay = (SpriteGo*)AddGameObject(new SpriteGo("graphics/mainmenu/menuoverlay.png"));
	overlay->sortingLayer = SortingLayers::Background;
	overlay->sortingOrder = 4;

	Scene::Init();
}

void SceneStart::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	Scene::Enter();

	background->SetScale({ 2.f,2.f });

	logo->GetSprite().setTextureRect(logoRect);
	logo->SetScale({ 2.f,2.f });
	logo->SetOrigin(Origins::MC);
	logo->SetPosition({ size.x * 0.5f, 120.f });

	pressStart->GetSprite().setTextureRect(pressRect[startIndex]);
	pressStart->SetScale({ 2.f,2.f });
	pressStart->SetOrigin(Origins::MC);
	pressStart->SetPosition({ size.x * 0.5f, 330.f});

	shading->SetScale({ 2.f,2.f });
	shading->SetOrigin(Origins::BL);
	shading->SetPosition({ 0, size.y });

	overlay->SetScale({ 2.f,2.f });

	sceneChanging = false;
}

void SceneStart::Update(float dt)
{
	Scene::Update(dt);

	pressChangeTime += dt;
	if (pressChangeTime >= pressChangeTimeMax)
	{
		pressStart->GetSprite().setTextureRect(pressRect[(++startIndex) % 2]);
		pressChangeTime = 0.f;
	}

	rotationTime += dt;
	logo->SetRotation(logo->GetRotation() + dt * 3 *rotationDir);
	if (rotationTime >= rotationTimeMax)
	{
		rotationDir *= -1.f;
		rotationTime = 0.f;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space) || InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sceneChanging = true;
		SOUND_MGR.PlaySfx("sounds/book page turn.wav");
	}
	if (sceneChanging)
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(1.f, 0.f) * dt * 800.f);
		if (worldView.getCenter().x >= FRAMEWORK.GetWindowSizeF().x * 1.5f)
		{
			SCENE_MGR.ChangeScene(SceneIds::Stage);
		}
	}
}
