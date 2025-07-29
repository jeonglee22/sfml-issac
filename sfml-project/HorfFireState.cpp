#include "stdafx.h"
#include "HorfFireState.h"
#include "Monster.h"
#include "Horf.h"

void HorfFireState::Enter(Monster* monster)
{
    shootTimer = 0.0f;
    hasShot = false;
    monster->GetAnimator().Play("animations/horf_fire.csv");
    monster->SetVelocity(sf::Vector2f(0, 0));
}

void HorfFireState::Update(Monster* monster, float dt)
{
    shootTimer += dt;

    if (!hasShot && shootTimer >= 0.3f)
    {
        Horf* horf = static_cast<Horf*>(monster);

        sf::Vector2f playerPos = monster->GetPlayerPosition();
        sf::Vector2f horfPos = monster->GetPosition();
        sf::Vector2f direction = playerPos - horfPos;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0)
        {
            direction /= length;
        }

        horf->FireProjectile(direction);
        hasShot = true;

        SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sounds/tear fire 4.wav"));
    }

    // 발사 애니메이션 완료 후 Idle로 복귀
    if (shootTimer >= shootDuration)
    {
        Horf* horf = static_cast<Horf*>(monster);
        horf->ChangeToIdleState();
    }
}

void HorfFireState::Exit(Monster* monster)
{
}