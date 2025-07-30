#pragma once
#include "MonsterState.h"

class PooterFireState : public MonsterState
{
protected:
    float shootTimer = 0.0f;
    float shootDuration = 0.5f;
    bool hasShot = false;

public:
    PooterFireState() {}
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "PooterFire"; }
};