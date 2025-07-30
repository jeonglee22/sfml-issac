#pragma once
#include "MonsterState.h"

class HorfFireState : public MonsterState
{
protected:
    float fireTimer = 0.0f;
    float fireDuration = 0.4f;
    bool hasFire = false;

public:
    HorfFireState() {}
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "Fire"; }
};


