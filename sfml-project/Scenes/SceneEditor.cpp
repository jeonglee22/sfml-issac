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
	texIds.push_back("graphics/obstacles/rocks/rocks_caves.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_depths.png");
	texIds.push_back("graphics/obstacles/rocks/rocks_sheol.png");
	texIds.push_back("graphics/obstacles/pit/grid_pit_basement.png");
	texIds.push_back("graphics/obstacles/pit/grid_pit_depths.png");
	texIds.push_back("graphics/obstacles/grid_fireplace.png");
	texIds.push_back("graphics/enemies/boss_001_larryjr.png");
	texIds.push_back("graphics/enemies/boss_004_monstro.png");
	texIds.push_back("graphics/enemies/monster_010_fly.png");
	texIds.push_back("graphics/enemies/monster_010_attackfly.png");
	texIds.push_back("graphics/enemies/monster_044_hopperleaper.png");
	texIds.push_back("graphics/enemies/monster_214_level2spider_small.png");
	texIds.push_back("graphics/enemies/monster_000_bodies02.png");
	texIds.push_back("graphics/additionals/grid_poop.png");
	texIds.push_back("graphics/additionals/levelitem_001_itemaltar.png");
	texIds.push_back("graphics/additionals/pickups/pickup_001_heart.png");
	texIds.push_back("graphics/additionals/pickups/heart.png");
	texIds.push_back("graphics/additionals/pickups/halfheart.png");
	texIds.push_back("graphics/additionals/pickups/pickup_002_coin.png");
	texIds.push_back("graphics/additionals/pickups/pickup_005_chests.png");
	texIds.push_back("graphics/additionals/pickups/pickup_003_key.png");
	texIds.push_back("graphics/additionals/pickups/pickup_016_bomb.png");
	texIds.push_back("graphics/enemies/monster_029_horf.png");
	texIds.push_back("graphics/enemies/monster_001_pooter.png");

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

	isSetDrop = false;
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
		sf::RectangleShape box = mapBox->GetRectHavePoint(mouseUIPos);
		if (box.getSize() != sf::Vector2f(0.f, 0.f) && CheckAlreadySetGrid(spriteChoosed) == nullptr && IsNotOnGrid())
		{
			SpriteGo* sprite = new SpriteGo(*spriteChoosed);
			sprite->SetScale(sprite->GetScale() * 2.f);
			sprite->SetPosition(ScreenToWorld(UiToScreen(box.getPosition())));
			sprite->sortingLayer = spriteChoosed->sortingLayer;
			sprite->sortingOrder = spriteChoosed->sortingOrder;
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
	if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		if (CheckAlreadySetGrid() != nullptr)
		{
			SpriteGo* sprite = CheckAlreadySetGrid();
			mapSprites.remove(sprite);
			RemoveGameObject(sprite);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::D) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(-468.f, 0.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::A) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(468.f, 0.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::W) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(0.f, 364.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::S) && !mapBox->GetCheckingMap())
	{
		worldView.setCenter(worldView.getCenter() + sf::Vector2f(0.f, -364.f));
	}
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

rapidcsv::Document SceneEditor::SaveFile()
{
	rapidcsv::Document doc;
	doc.SetColumnName(0,"TEXTURE_ID");
	doc.SetColumnName(1,"TEXTURERECT_TOP");
	doc.SetColumnName(2,"TEXTURERECT_LEFT");
	doc.SetColumnName(3,"TEXTURERECT_WIDTH");
	doc.SetColumnName(4,"TEXTURERECT_HEIGHT");
	doc.SetColumnName(5,"NAME");
	doc.SetColumnName(6,"XPOSITION");
	doc.SetColumnName(7,"YPOSITION");
	doc.SetColumnName(8,"WIDTH");
	doc.SetColumnName(9,"HEIGHT");
	doc.SetColumnName(10,"LAYER");
	doc.SetColumnName(11,"ORDER");
	doc.SetColumnName(12,"ROTATION");

	float left = INT_MAX, top = INT_MAX, right = INT_MIN, bottom = INT_MIN;

	std::vector<std::string> infos;

	int i = 1;
	for (auto sprite : mapSprites)
	{
		infos.clear();
		sf::Vector2f pos = sprite->GetPosition() - mapBox->GetTopLeft();
		sf::FloatRect bounds = sprite->GetSprite().getLocalBounds();
		infos.push_back(sprite->GetTextureId());
		infos.push_back(std::to_string(sprite->GetSprite().getTextureRect().top));
		infos.push_back(std::to_string(sprite->GetSprite().getTextureRect().left));
		infos.push_back(std::to_string(sprite->GetSprite().getTextureRect().width));
		infos.push_back(std::to_string(sprite->GetSprite().getTextureRect().height));

		if (left > pos.x)
			left = pos.x;
		if (top > pos.y)
			top = pos.y;
		if (right < pos.x + bounds.width * 2.f)
			right = pos.x + bounds.width * 2.f;
		if (bottom < pos.y + bounds.height * 2.f)
			bottom = pos.y + bounds.height * 2.f;

		infos.push_back(sprite->GetName());
		infos.push_back(std::to_string(pos.x));
		infos.push_back(std::to_string(pos.y));
		infos.push_back(std::to_string(bounds.width));
		infos.push_back(std::to_string(bounds.height));
		infos.push_back(std::to_string((int)sprite->sortingLayer));
		infos.push_back(std::to_string(sprite->sortingOrder));
		infos.push_back(std::to_string(sprite->GetRotation()));
		infos.push_back(std::to_string(sprite->GetOrigin().x));
		infos.push_back(std::to_string(sprite->GetOrigin().y));
		doc.InsertRow(i++, infos);
	}
	doc.SetCell(0, 0, left);
	doc.SetCell(1, 0, top);
	doc.SetCell(2, 0, right - left);
	doc.SetCell(3, 0, bottom - top);

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

	for (auto sprite : mapSprites)
	{
		RemoveGameObject(sprite);
	}
	mapSprites.clear();
	for (int i = 0; i < doc.GetRowCount()-1; i++)
	{
		std::vector<std::string> infos = doc.GetRow<std::string>(i+1);
		SpriteGo* loadSprite = new SpriteGo(infos[0], infos[5]);
		loadSprite->Init();
		loadSprite->SetOrigin(Origins::MC);
		loadSprite->Reset();
		loadSprite->GetSprite().setTextureRect({ std::stoi(infos[2]),std::stoi(infos[1]), std::stoi(infos[3]), std::stoi(infos[4]) });
		loadSprite->SetScale({2.f, 2.f});
		loadSprite->SetOrigin({ std::stof(infos[13]) , std::stof(infos[14]) });
		loadSprite->SetPosition(sf::Vector2f( std::stof(infos[6]), std::stof(infos[7]) ) + mapBox->GetTopLeft());
		loadSprite->SetRotation(std::stof(infos[12]));
		loadSprite->sortingLayer = (SortingLayers)std::stoi(infos[10]);
		loadSprite->sortingOrder = std::stoi(infos[11]);
		mapSprites.push_back(loadSprite);
		AddGameObject(loadSprite);
	}
}

SpriteGo* SceneEditor::CheckAlreadySetGrid(const SpriteGo* sp)
{
	auto mouseWorldPos = Scene::ScreenToWorld(InputMgr::GetMousePosition());
	auto it = mapSprites.begin();
	bool CanDrop = true;
	SpriteGo* result = new SpriteGo("","temp");
	while (it != mapSprites.end())
	{
		if (Utils::PointInTransformBounds((*it)->GetSprite(), (*it)->GetSprite().getLocalBounds(), mouseWorldPos))
		{
			if ((*it)->sortingLayer != sp->sortingLayer || (*it)->sortingOrder != sp->sortingOrder)
			{
				if (!CanDrop)
				{
					it++;
					continue;
				}
				delete result;
				result = nullptr;
			}
			else
			{
				CanDrop = false;
				if (result != nullptr)
				{
					delete result;
				}
				result = new SpriteGo(**it);
			}
		}
		it++;
	}
	if (result == nullptr || result->GetName() == "temp")
		return nullptr;
	return result;
}

SpriteGo* SceneEditor::CheckAlreadySetGrid()
{
	auto mouseWorldPos = Scene::ScreenToWorld(InputMgr::GetMousePosition());
	auto it = mapSprites.begin();
	while (it != mapSprites.end())
	{
		if (Utils::PointInTransformBounds((*it)->GetSprite(), (*it)->GetSprite().getLocalBounds(), mouseWorldPos))
		{
			return *it;
		}
		else
		{
			it++;
		}
	}
	return nullptr;
}

bool SceneEditor::IsNotOnGrid()
{
	auto mouseUIPos = Scene::ScreenToUi(InputMgr::GetMousePosition());
	auto grid = mapBox->GetMapGird();
	auto it = grid.begin();
	while (it != grid.end())
	{
		if (Utils::PointInTransformBounds(*it, (*it).getLocalBounds(), mouseUIPos))
		{
			return false;
		}
		else
		{
			it++;
		}
	}
	return true;
}

std::string SceneEditor::GetCurrentType() const
{
	return editBox->GetActiveType();
}
