#include "stdafx.h"
#include "DingleSummonState.h"
#include "Monster.h"
#include "Dingle.h"
#include "Dip.h"
#include "SceneGame.h"

void DingleSummonState::Enter(Monster* monster)
{
    monster->GetAnimator().Play("animations/dingle_summon.csv");
    summonTimer = 0.0f;
    hasSummoned = false;
}

void DingleSummonState::Update(Monster* monster, float dt)
{
    summonTimer += dt;

    if (!hasSummoned && summonTimer >= 1.0f)
    {
        Dingle* dingle = static_cast<Dingle*>(monster);
        SummonOneDip(dingle);
        hasSummoned = true;
    }

    if (summonTimer >= summonDuration)
    {
        Dingle* dingle = static_cast<Dingle*>(monster);
        dingle->ChangeToFireState();
    }
}

void DingleSummonState::Exit(Monster* monster)
{
}

void DingleSummonState::SummonOneDip(Dingle* dingle)
{
    SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    if (!scene)
    {
        return;
    }

    sf::Vector2f dinglePos = dingle->GetPosition();

    float angle = Utils::RandomRange(0.0f, 360.0f) * (3.14159f / 180.0f);
    float distance = Utils::RandomRange(60.0f, 120.0f);
    sf::Vector2f spawnPos = dinglePos + sf::Vector2f(cos(angle) * distance, sin(angle) * distance);

    Dip* newDip = new Dip("SummonedDip");
    newDip->Init();
    newDip->Reset();
    newDip->SetPosition(spawnPos);

    scene->AddGameObject(newDip);

    Map* currentMap = scene->GetCurrentMap();
    if (currentMap)
    {
        currentMap->AddMonsterToList(newDip);
    }
}