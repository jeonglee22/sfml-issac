#include "stdafx.h"
#include "SceneAnimator.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "SpriteGo.h"

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
	clearAnimation = (Button *)AddGameObject(new Button());

	Scene::Init();

	loadAnimation->SetButtonRectSize({180.f, 30.f});
	loadAnimation->SetButtonRectColor(sf::Color::Black);
	loadAnimation->SetButtonRectOrigin({90.f, 15.f});
	loadAnimation->SetButtonRectOutlineThickness(3.f);
	loadAnimation->SetTextSize(25);
	loadAnimation->SetTextOrigin(Origins::MC);

	loadFile->SetButtonRectSize({180.f, 30.f});
	loadFile->SetButtonRectOrigin({90.f, 15.f});
	loadFile->SetButtonRectOutlineThickness(3.f);
	loadFile->SetButtonRectOutlineColor(sf::Color::Black);
	loadFile->SetTextSize(25);
	loadFile->SetTextOrigin(Origins::MC);

	saveAnimation->SetButtonRectSize({180.f, 30.f});
	saveAnimation->SetButtonRectColor(sf::Color::Black);
	saveAnimation->SetButtonRectOrigin({90.f, 15.f});
	saveAnimation->SetButtonRectOutlineThickness(3.f);
	saveAnimation->SetTextSize(25);
	saveAnimation->SetTextOrigin(Origins::MC);

	clearAnimation->SetButtonRectSize({180.f, 30.f});
	clearAnimation->SetButtonRectColor(sf::Color::Black);
	clearAnimation->SetButtonRectOrigin({90.f, 15.f});
	clearAnimation->SetButtonRectOutlineThickness(3.f);
	clearAnimation->SetTextSize(25);
	clearAnimation->SetTextOrigin(Origins::MC);
}

void SceneAnimator::Enter()
{
	FRAMEWORK.GetWindow().setSize({1366, 768});
	auto size = FRAMEWORK.GetWindowSizeF();

	body.setSize({700.f, size.y });
	body.setOrigin({350.f, size.y * 0.5f});
	body.setPosition({size.x - body.getSize().x * 0.5f, size.y * 0.5f });

	line.setSize({ size.x, 2.f });
	line.setOrigin({ size.x * 0.5f, 1.f });
	line.setPosition({ size.x * 0.5f, 632.f});

	sf::Vector2f center{size.x * 0.5f, size.y * 0.5f};
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();

	loadAnimation->SetPosition({100.f, 50.f});
	loadAnimation->SetTextPosition({0.f, -10.f});
	loadAnimation->SetTextString("LoadAnimation");
	loadAnimation->SetButtonRectPosition({0.f, 0.f});
	loadAnimation->SetButtonFunc([this]() { LoadFile(true); });

	saveAnimation->SetPosition({300.f, 50.f});
	saveAnimation->SetTextPosition({0.f, -10.f});
	saveAnimation->SetTextString("SaveAnimation");
	saveAnimation->SetButtonRectPosition({0.f, 0.f});
	saveAnimation->SetButtonFunc([this]() { SaveFile(); });

	loadFile->SetPosition({ 1000.f, 50.f });
	loadFile->SetTextPosition({ 0.f, -10.f });
	loadFile->SetTextString("LoadFile");
	loadFile->SetTextColor(sf::Color::Black);
	loadFile->SetButtonRectPosition({ 0.f, 0.f });
	loadFile->SetButtonFunc([this]() { LoadFile(false); });

	clearAnimation->SetPosition({ 500.f, 50.f });
	clearAnimation->SetTextPosition({ 0.f, -10.f });
	clearAnimation->SetTextString("Clear");
	clearAnimation->SetButtonRectPosition({ 0.f, 0.f });
	clearAnimation->SetButtonFunc([this]() { ClearAnimationBox(); });
}

void SceneAnimator::Update(float dt)
{
	Scene::Update(dt);
	
	MoveAnimationClip();

	PickSpriteRect();

	if (InputMgr::GetKeyDown(sf::Keyboard::V))
	{
		ConvertToSpriteSheetPos();
	}

	animator.Update(dt);

	if (isLoading)
	{
		PlaySpritesFromLoad();
		isLoading = false;
	}
	else
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Q))
			AddPickSprite();
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
			RemoveSpriteInFrames();
	}
}

void SceneAnimator::Draw(sf::RenderWindow& window)
{
	for (auto box : animationFrameBoxes)
		window.draw(box);
	for (auto sprite : animationSprites)
		sprite->Draw(window);

	window.draw(body);
	window.draw(line);

	Scene::Draw(window);

	window.draw(spritePickRect);
	window.draw(spriteSheetOutline);
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

void SceneAnimator::LoadFile(bool isAnimation)
{
	CHAR filename[MAX_PATH] = "";
	CHAR currentFilePos[MAX_PATH] = "";
	GetCurrentDirectoryA(MAX_PATH, currentFilePos);

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "all files\0*.*\0txt files\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "csv";

	if (GetOpenFileNameA(&ofn) != NULL)
	{
		sprintf_s(filename, "%s", ofn.lpstrFile);
		MessageBoxA(hwnd, filename, "Load Choose", MB_OK);

		if (isAnimation)
			LoadAnimationFile(filename);
		else
			LoadSpriteFile(filename);

		SetCurrentDirectoryA(currentFilePos);
	}
}

void SceneAnimator::LoadAnimationFile(const std::string &fileName)
{
	isLoading = true;
	ClearAnimationBox();
	ANI_CLIP_MGR.Load(fileName);
	animation = ANI_CLIP_MGR.Get(fileName);
}

void SceneAnimator::LoadSpriteFile(const std::string& fileName)
{
	if (spriteField != nullptr)
		RemoveGameObject(spriteField);
	TEXTURE_MGR.Load(fileName);
	spriteSheetName = fileName;

	spriteField = new SpriteGo(fileName);
	spriteField->Reset();
	AddGameObject(spriteField);
	spriteField->SetPosition(body.getPosition() - spriteField->GetSprite().getLocalBounds().getSize() * 0.5f);
	spriteSheetOutline = sf::RectangleShape();
	spriteSheetOutline.setFillColor(sf::Color::Transparent);
	spriteSheetOutline.setOutlineColor(sf::Color::Blue);
	spriteSheetOutline.setOutlineThickness(1.f);
	spriteSheetOutline.setPosition(body.getPosition() - spriteField->GetSprite().getLocalBounds().getSize() * 0.5f);
	spriteSheetOutline.setSize(spriteField->GetSprite().getLocalBounds().getSize());
}

void SceneAnimator::PlaySpritesFromLoad()
{
	if (animationBody != nullptr)
	{
		RemoveGameObject(animationBody);
	}
	animator = Animator();

	animationBody = new SpriteGo();
	AddGameObject(animationBody);
	animationBody->sortingLayer = SortingLayers::Foreground;
	animationBody->sortingOrder = 0;

	texIds.push_back((*animation.frames.begin()).texId);
	TEXTURE_MGR.Load(texIds);
	animationBody->GetSprite().setTexture(TEXTURE_MGR.Get((*animation.frames.begin()).texId));
	animationBody->GetSprite().setTextureRect((*animation.frames.begin()).texCoord);
	animationBody->SetOrigin(Origins::MC);
	animationBody->SetPosition(worldView.getCenter() - sf::Vector2f(350.f, 100.f));
	animationBody->SetScale({ 2.f,2.f });

	for (auto frame : animation.frames)
	{
		AddEachAnimationSpriteFrame(frame);
	}

	animator.SetTarget(&animationBody->GetSprite());
	animator.Play(&animation);
}

void SceneAnimator::MoveAnimationClip()
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && 
		(InputMgr::GetMousePosition().y >= 632.f && InputMgr::GetMousePosition().x <= 666.f) && !isClipDrag)
	{
		isClipDrag = true;
		beforeMousePosX = InputMgr::GetMousePosition().x;
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isClipDrag)
	{
		afterMousePosX = InputMgr::GetMousePosition().x;
		for (int i = 0; i < animationFrameBoxes.size(); i++)
		{
			animationFrameBoxes[i].setPosition(animationFrameBoxesInitPos[i] + sf::Vector2f(afterMousePosX - beforeMousePosX, 0.f));
			animationSprites[i]->SetPosition(animationFrameBoxes[i].getPosition() + sf::Vector2f(50.f, 50.f));
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isClipDrag)
	{
		isClipDrag = false;
		for (int i = 0; i < animationFrameBoxes.size(); i++)
		{
			animationFrameBoxesInitPos[i] = animationFrameBoxes[i].getPosition();
		}
	}
}

void SceneAnimator::PickSpriteRect()
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) &&
		(InputMgr::GetMousePosition().x >= 666.f) && !isSpritePick)
	{
		sf::Vector2f mousePos = ScreenToWorld( InputMgr::GetMousePosition());
		if (Utils::PointInTransformBounds(spriteField->GetSprite(), spriteField->GetSprite().getLocalBounds(), mousePos))
		{
			spritePickRect = sf::RectangleShape();
			spritePickRect.setFillColor(sf::Color::Transparent);
			spritePickRect.setOutlineColor(sf::Color::Red);
			spritePickRect.setOutlineThickness(2.f);
			spritePickRect.setPosition(mousePos);
			isSpritePick = true;
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isSpritePick)
	{
		sf::Vector2f mousePos = ScreenToWorld(InputMgr::GetMousePosition());
		spritePickRect.setSize(mousePos - spritePickRect.getPosition());
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isSpritePick)
	{
		isSpritePick = false;
	}
}

sf::IntRect SceneAnimator::ConvertToSpriteSheetPos()
{
	sf::Vector2f pos = spriteField->GetPosition();

	sf::IntRect rect;
	rect.left = std::roundf(spritePickRect.getPosition().x - pos.x);
	rect.top = std::roundf(spritePickRect.getPosition().y - pos.y);
	rect.width = std::roundf(spritePickRect.getSize().x);
	rect.height = std::roundf(spritePickRect.getSize().y);
	return rect;
}

void SceneAnimator::ClearAnimationBox()
{
	animationFrames.clear();
	animationSprites.clear();
	animationFrameBoxes.clear();
	animationFrameBoxesInitPos.clear();

	animator = Animator();
	animation = AnimationClip();

	if(animationBody)
	{
		RemoveGameObject(animationBody);
	}
	animationBody = nullptr;
}

void SceneAnimator::AddPickSprite()
{
	if (animationBody == nullptr)
	{
		animationBody = new SpriteGo(spriteSheetName);
		AddGameObject(animationBody);
		animationBody->sortingLayer = SortingLayers::Foreground;
		animationBody->sortingOrder = 0;

		texIds.push_back(spriteSheetName);
		TEXTURE_MGR.Load(texIds);

		animationBody->GetSprite().setTexture(TEXTURE_MGR.Get(spriteSheetName), true);
		animationBody->GetSprite().setTextureRect(ConvertToSpriteSheetPos());
		animationBody->SetOrigin(Origins::MC);
		animationBody->SetPosition(worldView.getCenter() - sf::Vector2f(350.f, 100.f));
		std::cout << animationBody->GetPosition().x << ", " << animationBody->GetPosition().y << std::endl;
		animationBody->SetScale({ 2.f,2.f });
	}

	animation.frames.push_back({ spriteSheetName , ConvertToSpriteSheetPos() });
	AddEachAnimationSpriteFrame(animation.frames.back());

	animator.SetTarget(&animationBody->GetSprite());
	animator.Play(&animation);
}

void SceneAnimator::RemoveSpriteInFrames()
{
}

void SceneAnimator::AddEachAnimationSpriteFrame(AnimationFrame frame)
{
	animationSprites.push_back(new SpriteGo());
	animationSprites[animationSprites.size() - 1]->SetTextureId(frame.texId);
	animationSprites[animationSprites.size() - 1]->Init();
	animationSprites[animationSprites.size() - 1]->sortingLayer = SortingLayers::Foreground;
	animationSprites[animationSprites.size() - 1]->sortingOrder = 0;
	animationSprites[animationSprites.size() - 1]->Reset();
	animationSprites[animationSprites.size() - 1]->GetSprite().setTextureRect(frame.texCoord);
	animationSprites[animationSprites.size() - 1]->SetOrigin((sf::Vector2f)frame.texCoord.getSize() * 0.5f);
	sf::RectangleShape rect;
	rect.setOutlineThickness(3.f);
	rect.setFillColor(sf::Color::Transparent);
	rect.setSize({ 100.f,100.f });
	sf::Vector2f pos = { 18.f + animationFrameBoxes.size() * 120.f, 650.f };
	animationFrameBoxesInitPos.push_back(pos);
	rect.setPosition(pos);
	animationSprites[animationSprites.size() - 1]->SetPosition(pos + sf::Vector2f(50.f, 50.f));
	animationSprites[animationSprites.size() - 1]->SetScale({ 100.f / frame.texCoord.width, 100.f / frame.texCoord.height });
	animationFrameBoxes.push_back(rect);
}
