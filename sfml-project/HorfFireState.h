#pragma once
#include "MonsterState.h"

class HorfFireState : public MonsterState
{
protected:


public:
    HorfFireState() {}
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "Fire"; }
};


