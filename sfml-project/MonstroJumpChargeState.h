#pragma once
#include "MonsterState.h"

class MonstroJumpChargeState : public MonsterState
{
protected:
    float chargeTimer;
    float chargeDuration;

public:
    MonstroJumpChargeState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MonstroJumpCharge"; }
};
