#include "stdafx.h"
#include "Fly.h"
#include "IdleState.h"
#include "WanderState.h"
#include "SceneGame.h"
#include "Obstacles.h"

Fly::Fly(const std::string& name)
	:Monster(name, Monsters::Fly)
{
}

void Fly::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;

    SetHP(30);
    SetSpeed(50.0f);
    SetDetectionRange(120.0f);
    SetSkillCooldown(4.0f);

    animator.Play("animations/fly.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    SetInitialState();
}

void Fly::UseSkill()
{
}

void Fly::SetInitialState()
{
    ChangeState(&wanderState);
}

sf::FloatRect Fly::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return { bodyGlobalBounds.left + 30.f, bodyGlobalBounds.top + 30.f, bodyGlobalBounds.width - 60.f, bodyGlobalBounds.height - 60.f };
}
