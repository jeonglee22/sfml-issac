#pragma once
#include "MonsterState.h"

class LarryMoveState : public MonsterState
{
protected:
    int lastDirectionIndex;

public:
    LarryMoveState();
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "LarryMove"; }
    void UpdateAnimation(Monster* monster, int currentDirectionIndex);
};
