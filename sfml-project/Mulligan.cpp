#include "stdafx.h"
#include "Mulligan.h"

Mulligan::Mulligan(const std::string& name)
	:Monster(name, Monsters::Mulligan)
{
}

//void Mulligan::Init()
//{
//
//
//
//
//}

void Mulligan::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 2;

    SetHP(130);
    SetSpeed(50.0f);
    SetDetectionRange(200.0f);
    SetSkillCooldown(3.0f);
   
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;
    skillCooldown = 3.0f;

    SetInitialState();
}

void Mulligan::UseSkill()
{
}

void Mulligan::SetInitialState()
{
	
}
