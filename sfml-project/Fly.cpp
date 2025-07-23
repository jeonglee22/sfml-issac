#include "stdafx.h"
#include "Fly.h"
#include "IdleState.h"
#include "WanderState.h"

WanderState Fly::wanderState;

Fly::Fly(const std::string& name)
	:Monster(name, Monsters::Fly)
{
}

void Fly::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;

    SetHP(1);
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
