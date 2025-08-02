#pragma once
#include "MonsterState.h"

class MonstroFireState : public MonsterState
{
protected:
    float fireTimer;
    float fireDuration;
    bool hasFired;

public:
    MonstroFireState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MonstroFire"; }
};

