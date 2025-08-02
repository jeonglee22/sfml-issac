#pragma once
#include "MonsterState.h"

class MonstroLandingState : public MonsterState
{
protected:
    float landingTimer;
    float landingDuration;
    bool hasLanded;

public:
    MonstroLandingState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MonstroLanding"; }
};

