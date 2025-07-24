#include "stdafx.h"
#include "SceneGame.h"
#include "rapidcsv.h"
#include "SpriteGo.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Stage)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/background/basement.png");
	texIds.push_back("graphics/background/sheol.png");
	texIds.push_back("graphics/background/caves.png");
	texIds.push_back("graphics/background/depths.png");
	texIds.push_back("graphics/obstacles/grid_spikes.png");
	texIds.push_back("graphics/obstacles/grid_fireplace.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_basement.png");
	texIds.push_back("graphics/obstacles/pit/grid_pit_basement.png");

	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);

	size = sf::Vector2f(960.f, 570.f);
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	Scene::Enter();

	LoadStageField("Mapfolder/testmap3.csv");
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::LoadStageField(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	mapSprites.clear();
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		std::vector<std::string> infos = doc.GetRow<std::string>(i);
		mapSprites.push_back(new SpriteGo(infos[0], infos[5]));
		mapSprites[i]->Init();
		mapSprites[i]->SetOrigin(Origins::MC);
		mapSprites[i]->Reset();
		mapSprites[i]->GetSprite().setTextureRect({std::stoi(infos[2]),std::stoi(infos[1]), std::stoi(infos[3]), std::stoi(infos[4]) });
		mapSprites[i]->SetScale({ 2.f,2.f });
		mapSprites[i]->SetOrigin({ std::stof(infos[13]) ,std::stof(infos[14]) });
		mapSprites[i]->SetPosition(sf::Vector2f( std::stof(infos[6]), std::stof(infos[7]) ) + sf::Vector2f(140.f, 104.f));
		mapSprites[i]->SetRotation(std::stof(infos[12]));
		mapSprites[i]->sortingLayer = (SortingLayers) std::stoi(infos[10]);
		mapSprites[i]->sortingOrder = std::stoi(infos[11]);
		AddGameObject(mapSprites[i]);
	}
}
