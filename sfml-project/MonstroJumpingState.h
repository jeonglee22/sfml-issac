#pragma once
#include "MonsterState.h"

class MonstroJumpingState : public MonsterState
{
protected:
    float jumpTimer;
    float jumpDuration;

public:
    MonstroJumpingState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MonstroJumping"; }
};
