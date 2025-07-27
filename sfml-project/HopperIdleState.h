#pragma once
#include "MonsterState.h"
class HopperIdleState : public MonsterState
{
protected:
    float idleTimer;
    float idleDuration;

    static std::random_device rd;
    std::mt19937 gen;

public:
    HopperIdleState();
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "HopperIdle"; }
};

