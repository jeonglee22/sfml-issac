#pragma once
#include "MonsterState.h"
class MonstroSmallJumpState : public MonsterState
{
protected:
    float jumpTimer;
    float jumpDuration;

public:
    MonstroSmallJumpState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MonstroSmallJump"; }
};

