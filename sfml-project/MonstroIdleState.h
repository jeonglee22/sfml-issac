#pragma once
#include "MonsterState.h"

class MonstroIdleState : public MonsterState
{
protected:
    float idleTimer;
    float idleDuration;

public:
    MonstroIdleState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MonstroIdle"; }
};

