#pragma once
#include "MonsterState.h"

class HorfFireState : public MonsterState
{
protected:
    float shootTimer = 0.0f;
    float shootDuration = 0.4f;
    bool hasShot = false;

public:
    HorfFireState() {}
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "Fire"; }
};


