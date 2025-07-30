#pragma once
#include "MonsterState.h"
#include "Monster.h"
#include "HorfFIreState.h"

class IdleState : public MonsterState
{
protected:
    HorfFireState horfFireState;

public:
    IdleState() {}

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "Idle"; }
};

