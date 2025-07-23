#include "stdafx.h"
#include "windows.h"
#include "commdlg.h"
#include "SceneEditor.h"
#include "EditBoxUI.h"
#include "MapBoxUI.h"
#include "Button.h"

HWND hwnd;

SceneEditor::SceneEditor()
	: Scene(SceneIds::Editor)
{
}

void SceneEditor::Init()
{
	texIds.push_back("graphics/background/basement.png");
	texIds.push_back("graphics/background/sheol.png");
	texIds.push_back("graphics/background/caves.png");
	texIds.push_back("graphics/background/depths.png");
	texIds.push_back("graphics/obstacles/grid_spikes.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_basement.png");

	fontIds.push_back("fonts/DS-DIGIT.TTF");

	editBox = (EditBoxUI*)AddGameObject(new EditBoxUI());
	mapBox = (MapBoxUI*)AddGameObject(new MapBoxUI());

	load = (Button*)AddGameObject(new Button());
	save = (Button*)AddGameObject(new Button());

	Scene::Init();

	load->SetButtonRectSize({ 70.f, 30.f });
	load->SetButtonRectColor(sf::Color::Black);
	load->SetButtonRectOrigin({ 35.f, 15.f });
	load->SetButtonRectOutlineThickness(3.f);
	load->SetTextSize(25);

	save->SetButtonRectSize({ 70.f, 30.f });
	save->SetButtonRectColor(sf::Color::Black);
	save->SetButtonRectOrigin({ 35.f, 15.f });
	save->SetButtonRectOutlineThickness(3.f);
	save->SetTextSize(25);
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

	load->SetPosition({ 100.f, 50.f });
	load->SetTextPosition({ 0.f, -10.f });
	load->SetTextString("Load");
	load->SetButtonRectPosition({ 0.f,0.f });
	load->SetButtonFunc([this]() {LoadField(); });

	save->SetPosition({ 200.f, 50.f });
	save->SetTextPosition({ 0.f, -10.f });
	save->SetTextString("Save");
	save->SetButtonRectPosition({ 0.f,0.f });
	save->SetButtonFunc([this]() {SaveField(); });
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);

	auto mouseUIPos = Scene::ScreenToUi(InputMgr::GetMousePosition());
	auto mouseWorldPos = Scene::ScreenToWorld(InputMgr::GetMousePosition());
	editBoxBody = editBox->GetMainUIBody();
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && 
		Utils::PointInTransformBounds(editBoxBody, editBoxBody.getLocalBounds(), mouseUIPos))
	{
		std::vector<SpriteGo*> sprites = editBox->GetActiveSprites();
		for (auto sprite : sprites)
		{
			if (Utils::PointInTransformBounds(sprite->GetSprite(), sprite->GetSprite().getLocalBounds(), mouseUIPos))
			{
				isChoosed = true;
				spriteChoosed = editBox->SetChoosedSprite(sprite);
			}
		}
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && isChoosed)
	{
		sf::Vector2f boxPos = mapBox->GetRectCenterHavePoint(mouseUIPos);
		if (boxPos != sf::Vector2f(0.f,0.f))
		{
			SpriteGo* sprite = new SpriteGo(*spriteChoosed);
			sprite->SetOrigin(Origins::MC);
			sprite->SetPosition(ScreenToWorld(UiToScreen(boxPos)));
			sprite->sortingLayer = SortingLayers::Foreground;
			sprite->sortingOrder = 1;
			AddGameObject(sprite);
			mapSprites.push_back(sprite);
		}
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && 
		Utils::PointInTransformBounds(editBoxBody, editBoxBody.getLocalBounds(), mouseUIPos))
	{
		isChoosed = false;
		editBox->SetOffChoosedSprite();
		spriteChoosed = nullptr;
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		auto it = mapSprites.begin();
		while(it != mapSprites.end())
		{
			if (Utils::PointInTransformBounds((*it)->GetSprite(), (*it)->GetSprite().getLocalBounds(), mouseWorldPos))
			{
				RemoveGameObject(*it);
				it = mapSprites.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::D) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(-60.f, 0.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::A) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(60.f, 0.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::W) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(0.f, 60.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(0.f, -60.f));
	}
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

rapidcsv::Document SceneEditor::SaveFile()
{
	rapidcsv::Document doc;

	//sprites();

	return doc;
}

void SceneEditor::SaveField()
{
	rapidcsv::Document doc = SaveFile();

	CHAR filename[MAX_PATH] = "";
	CHAR currentFilePos[MAX_PATH] = "";
	GetCurrentDirectoryA(MAX_PATH, currentFilePos);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "모든 파일\0*.*\0텍스트 파일\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = "csv";

	while (true)
	{
		if (GetSaveFileNameA(&ofn) != NULL)
		{
			sprintf_s(filename, "%s", ofn.lpstrFile);
			MessageBoxA(hwnd, filename, "Save Choose", MB_OK);

			doc.Save(filename);
			SetCurrentDirectoryA(currentFilePos);
			break;
		}
		else
		{
			continue;
		}
	}
}

void SceneEditor::LoadField()
{
	CHAR filename[MAX_PATH] = "";
	CHAR currentFilePos[MAX_PATH] = "";
	GetCurrentDirectoryA(MAX_PATH, currentFilePos);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "모든 파일\0*.*\0텍스트 파일\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "csv";

	if (GetOpenFileNameA(&ofn) != NULL)
	{
		sprintf_s(filename, "%s", ofn.lpstrFile);
		MessageBoxA(hwnd, filename, "Load Choose", MB_OK);

		LoadFile(filename);

		SetCurrentDirectoryA(currentFilePos);
	}
}

void SceneEditor::LoadFile(const std::string& fileName)
{
	rapidcsv::Document doc(fileName);
}