#include "stdafx.h"
#include "MulliganDeathState.h"
#include "Monster.h"
#include "Mulligan.h"
#include "SceneGame.h"
#include "Fly.h"

MulliganDeathState::MulliganDeathState()
    : deathTimer(0.0f), faceSwelled(false), exploded(false)
{
    faceSwellDuration = 0.5f;
    explosionDuration = 1.0f;
}

void MulliganDeathState::Enter(Monster* monster)
{
    deathTimer = 0.0f;
    faceSwelled = false;
    exploded = false;

    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/mulligan_dead.csv");
    std::cout << "멀리건 데드애니메이션 엔터!" << std::endl;
}

void MulliganDeathState::Update(Monster* monster, float dt)
{
    deathTimer += dt;

    if (!faceSwelled && deathTimer >= faceSwellDuration)
    {
        faceSwelled = true;
    }

    if (!exploded && deathTimer >= explosionDuration)
    {
        exploded = true;

        SpawnFlies(monster);

        Mulligan* mulligan = static_cast<Mulligan*>(monster);
        mulligan->BodyAnimatorPlayEmpty();

        monster->GetAnimator().Play("animations/blood_small.csv");

        SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/death burst small.wav"));
    }
    if (exploded && deathTimer >= explosionDuration + 0.5f)
    {
        monster->SetActive(false);
    }
}

void MulliganDeathState::Exit(Monster* monster)
{
}

void MulliganDeathState::SpawnFlies(Monster* monster)
{
    SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
    if (!scene)
    {
        return;
    }

    sf::Vector2f mulliganPos = monster->GetPosition();
    mulliganPos.y -= 30.0f;

    for (int i = 0; i < 3; i++)
    {
        Fly* fly = new Fly("Fly");
        fly->Init();
        fly->Reset();

        float angle = (2.0f * 3.14159f * i) / 3.0f + Utils::RandomRange(-0.3f, 0.3f);
        float distance = Utils::RandomRange(15.0f, 25.0f);

        sf::Vector2f spawnPos = mulliganPos + sf::Vector2f(
            cos(angle) * distance,
            sin(angle) * distance
        );

        fly->SetPosition(spawnPos);
        scene->AddGameObject(fly);

        Map* currentMap = scene->GetCurrentMap();
        if (currentMap)
        {
            currentMap->AddMonsterToList(fly);
        }
    }
}
