#include "stdafx.h"
#include "HorfFireState.h"
#include "Monster.h"

void HorfFireState::Enter(Monster* monster)
{
    monster->SetVelocity(sf::Vector2f(0, 0));
}

void HorfFireState::Update(Monster* monster, float dt)
{

    if (monster->GetMonsterType() == Monsters::Horf)
    {

        
    }


}

void HorfFireState::Exit(Monster* monster)
{
    monster->SetVelocity(sf::Vector2f(0, 0));
}