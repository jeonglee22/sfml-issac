#include "stdafx.h"
#include "SpriteGo.h"
#include "SceneChange.h"

SceneChange::SceneChange()
	: Scene(SceneIds::Change)
{
}

void SceneChange::Init()
{
	texIds.push_back("graphics/nightmares_bg.png");
	texIds.push_back("graphics/progress.png");
	texIds.push_back("graphics/playerportraitbig_01_isaac.png");

	background = (SpriteGo*)AddGameObject(new SpriteGo("graphics/nightmares_bg.png"));
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

	playerImage = (SpriteGo*)AddGameObject(new SpriteGo("graphics/playerportraitbig_01_isaac.png"));
	playerImage->sortingLayer = SortingLayers::Background;
	playerImage->sortingOrder = 3;

	for (int i = 0; i < maxStageCount; i++)
	{
		stages.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/progress.png")));
		stages[i]->sortingLayer = SortingLayers::Foreground;
		stages[i]->sortingOrder = 2;

		clearStages.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/progress.png")));
		clearStages[i]->sortingLayer = SortingLayers::Foreground;
		clearStages[i]->sortingOrder = 3;
		clearStages[i]->SetActive(false);

		if(i < maxStageCount-1)
		{
			stageConnects.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/progress.png")));
			stageConnects[i]->sortingLayer = SortingLayers::Foreground;
			stageConnects[i]->sortingOrder = 1;
		}
	}

	playerIcon = (SpriteGo*)AddGameObject(new SpriteGo("graphics/progress.png"));
	playerIcon->sortingLayer = SortingLayers::Foreground;
	playerIcon->sortingOrder = 4;

	Scene::Init();
}

void SceneChange::Enter()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	Scene::Enter();

	background->SetScale({ 2.f,2.f });

	playerImage->SetOrigin(Origins::MC);
	playerImage->SetScale({ 2.f,2.f });
	playerImage->SetPosition({worldView.getCenter()+ sf::Vector2f(0, 100.f)});

	for (int i = 0; i< maxStageCount; i++)
	{
		auto stage = stages[i];
		stage->GetSprite().setTextureRect(stageRect);
		stage->SetOrigin(Origins::MC);
		stage->SetScale({ 2.f,2.f });
		stage->SetPosition({ worldView.getCenter().x + (i - 2) * 30.f * 2.f,50.f});
		std::cout << SCENE_MGR.GetClearedScene() << std::endl;
		if(i <= SCENE_MGR.GetClearedScene())
		{
			clearStages[i]->SetActive(true);
			clearStages[i]->GetSprite().setTextureRect(clearRect);
			clearStages[i]->SetOrigin(Origins::MC);
			clearStages[i]->SetScale({ 2.f,2.f });
			clearStages[i]->SetPosition({ worldView.getCenter().x + (i - 2) * 30.f * 2.f,50.f });
		}

		if(i < maxStageCount -1)
		{
			auto stageconnect = stageConnects[i];
			stageconnect->GetSprite().setTextureRect(stageconnetRect);
			stageconnect->SetOrigin(Origins::MC);
			stageconnect->SetScale({ 2.f,2.f });
			stageconnect->SetPosition(stage->GetPosition() + sf::Vector2f(30.f, 0.f));
		}
	}

	playerIcon->GetSprite().setTextureRect(playerIconRect);
	playerIcon->SetOrigin(Origins::MC);
	playerIcon->SetScale({ 2.f,2.f });
	playerIcon->SetPosition(stages[SCENE_MGR.GetClearedScene()]->GetPosition());

	sceneDelayTime = 0.f;
	iconMoveTime = 0.f;

	SCENE_MGR.SetClearedScene(SCENE_MGR.GetClearedScene() + 1);
}

void SceneChange::Update(float dt)
{
	if (SCENE_MGR.GetClearedScene() == 5)
	{
		SCENE_MGR.ChangeScene(SceneIds::Start);
		return;
	}
	Scene::Update(dt);

	sceneDelayTime += dt;
	if (sceneDelayTime <= sceneDelayTimeMax)
	{
		return;
	}

	sf::Vector2f pos = playerIcon->GetPosition();
	iconMoveTime += dt;
	pos.x = Utils::Lerp(stages[SCENE_MGR.GetClearedScene()-1]->GetPosition().x, stages[SCENE_MGR.GetClearedScene()]->GetPosition().x, (float) iconMoveTime / iconMoveTimeMax);
	playerIcon->SetPosition(pos);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Stage);
	}
}