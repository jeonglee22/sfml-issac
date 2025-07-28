#include "stdafx.h"
#include "SceneAnimator.h"
#include "AnimationClip.h"
#include "Animator.h"

SceneAnimator::SceneAnimator()
	: Scene(SceneIds::Animator)
{
}

void SceneAnimator::Init()
{
	fontIds.push_back("fonts/DS-DIGIT.TTF");

	loadAnimation = (Button *)AddGameObject(new Button());
	loadFile = (Button *)AddGameObject(new Button());
	saveAnimation = (Button *)AddGameObject(new Button());

	Scene::Init();

	loadAnimation->SetButtonRectSize({180.f, 30.f});
	loadAnimation->SetButtonRectColor(sf::Color::Black);
	loadAnimation->SetButtonRectOrigin({90.f, 15.f});
	loadAnimation->SetButtonRectOutlineThickness(3.f);
	loadAnimation->SetTextSize(25);
	loadAnimation->SetTextOrigin(Origins::MC);

	loadFile->SetButtonRectSize({180.f, 30.f});
	loadFile->SetButtonRectColor(sf::Color::Black);
	loadFile->SetButtonRectOrigin({90.f, 15.f});
	loadFile->SetButtonRectOutlineThickness(3.f);
	loadFile->SetTextSize(25);
	loadFile->SetTextOrigin(Origins::MC);

	saveAnimation->SetButtonRectSize({180.f, 30.f});
	saveAnimation->SetButtonRectColor(sf::Color::Black);
	saveAnimation->SetButtonRectOrigin({90.f, 15.f});
	saveAnimation->SetButtonRectOutlineThickness(3.f);
	saveAnimation->SetTextSize(25);
	saveAnimation->SetTextOrigin(Origins::MC);
}

void SceneAnimator::Enter()
{
	FRAMEWORK.GetWindow().setSize({1366, 768});
	auto size = FRAMEWORK.GetWindowSizeF();

	sf::Vector2f center{size.x * 0.5f, size.y * 0.5f};
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();

	loadAnimation->SetPosition({300.f, 50.f});
	loadAnimation->SetTextPosition({0.f, -10.f});
	loadAnimation->SetTextString("LoadAnimation");
	loadAnimation->SetButtonRectPosition({0.f, 0.f});
	loadAnimation->SetButtonFunc([this]()
								 { LoadField(); });

	loadFile->SetPosition({100.f, 50.f});
	loadFile->SetTextPosition({0.f, -10.f});
	loadFile->SetTextString("LoadFile");
	loadFile->SetButtonRectPosition({0.f, 0.f});
	loadFile->SetButtonFunc([this]()
							{ LoadField(); });

	saveAnimation->SetPosition({500.f, 50.f});
	saveAnimation->SetTextPosition({0.f, -10.f});
	saveAnimation->SetTextString("SaveAnimation");
	saveAnimation->SetButtonRectPosition({0.f, 0.f});
	saveAnimation->SetButtonFunc([this]()
								 { SaveFile(); });
}

void SceneAnimator::Update(float dt)
{
	Scene::Update(dt);
	if (animator)
		animator->Update(dt);
	else
	{
		if (animation != nullptr)
		{
			animationBody = new sf::Sprite();
			texIds.push_back((*animation->frames.begin()).texId);
			TEXTURE_MGR.Load(texIds);
			animationBody->setTexture(TEXTURE_MGR.Get((*animation->frames.begin()).texId));
			animationBody->setTextureRect((*animation->frames.begin()).texCoord);
			animator->SetTarget(animationBody);
			animator->Play(animation);
		}
	}
}

rapidcsv::Document SceneAnimator::SaveAnimation()
{
	rapidcsv::Document doc;
	/*doc.SetColumnName(0, "TEXTURE_ID");
	doc.SetColumnName(1, "FPS");
	doc.SetColumnName(2, "LOOPTYPE(0:Single, 1:Loop)");
	doc.SetCell(0, 0, animation->id);
	doc.SetCell(1, 0, animation->fps);
	doc.SetCell(2, 0, animation->loopType);

	float left = INT_MAX, top = INT_MAX, right = INT_MIN, bottom = INT_MIN;

	std::vector<std::string> infos;

	doc.SetCell(0, 2, "TEXTUREID");
	doc.SetCell(1, 2, "LEFT");
	doc.SetCell(2, 2, "TOP");
	doc.SetCell(3, 2, "HEIGHT");
	doc.SetCell(4, 2, "WIDTH");
	doc.SetCell(5, 2, "FLIPX(0:False, 1:True)");

	int i = 3;
	for (auto frame : animation->frames)
	{
		infos.clear();

		infos.push_back(frame.texId);
		infos.push_back(std::to_string(frame.texCoord.left));
		infos.push_back(std::to_string(frame.texCoord.top));
		infos.push_back(std::to_string(frame.texCoord.width));
		infos.push_back(std::to_string(frame.texCoord.height));
		infos.push_back(std::to_string(0));

		doc.InsertRow(i++, infos);
	}*/

	return doc;
}

void SceneAnimator::SaveFile()
{
	rapidcsv::Document doc = SaveAnimation();

	/*CHAR filename[MAX_PATH] = "";
	CHAR currentFilePos[MAX_PATH] = "";
	GetCurrentDirectoryA(MAX_PATH, currentFilePos);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "��� ����\0*.*\0�ؽ�Ʈ ����\0";
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
	}*/
}

void SceneAnimator::LoadField()
{
	CHAR filename[MAX_PATH] = "";
	CHAR currentFilePos[MAX_PATH] = "";
	GetCurrentDirectoryA(MAX_PATH, currentFilePos);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "��� ����\0*.*\0�ؽ�Ʈ ����\0";
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

void SceneAnimator::LoadFile(const std::string &fileName)
{
	animation->loadFromFile(fileName);
	ANI_CLIP_MGR.Load(animation->id);
}