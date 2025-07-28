#include "stdafx.h"
#include "LarryMoveState.h"
#include "Monster.h"
#include "LarryJr.h"

LarryMoveState::LarryMoveState()
    : lastDirectionIndex(-1)
{
}

void LarryMoveState::Enter(Monster* monster)
{
    lastDirectionIndex = -1;
    LarryJr* larry = static_cast<LarryJr*>(monster);
    UpdateAnimation(monster, larry->GetCurrentDirectionIndex());
}

void LarryMoveState::Update(Monster* monster, float dt)
{
    LarryJr* larry = static_cast<LarryJr*>(monster);

    larry->UpdateTurnTimer(dt);

    int currentDirectionIndex = larry->GetCurrentDirectionIndex();
    if (currentDirectionIndex != lastDirectionIndex)
    {
        UpdateAnimation(monster, currentDirectionIndex);
        lastDirectionIndex = currentDirectionIndex;
    }

    sf::Vector2f direction = larry->GetCurrentDirection();
    float speed = monster->GetSpeed();
    monster->SetVelocity(direction * speed);

    larry->UpdateBodyMovement(dt);
}

void LarryMoveState::UpdateAnimation(Monster* monster, int currentDirectionIndex)
{
    switch (currentDirectionIndex)
    {
    case 0:
        monster->GetAnimator().Play("animations/boss_larry_jr_head_rare.csv");
        monster->SetScale({ 2.0f, 2.0f });
        break;
    case 1:
        monster->GetAnimator().Play("animations/boss_larry_jr_head_side.csv");
        monster->SetScale({ 2.0f, 2.0f });
        break;
    case 2:
        monster->GetAnimator().Play("animations/boss_larry_jr_head_front.csv");
        monster->SetScale({ 2.0f, 2.0f });
        break;
    case 3:
        monster->GetAnimator().Play("animations/boss_larry_jr_head_side.csv");
        monster->SetScale({ -2.0f, 2.0f });
        break;
    }
}

void LarryMoveState::Exit(Monster* monster)
{
    monster->SetVelocity(sf::Vector2f(0, 0));
}
