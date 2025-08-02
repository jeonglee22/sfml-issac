#pragma once
#include "MonsterState.h"
class MulliganFleeState : public MonsterState
{
protected:

public:
    MulliganFleeState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MulliganFlee"; }
};

