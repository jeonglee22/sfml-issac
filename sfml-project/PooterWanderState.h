#pragma once
#include "MonsterState.h"

class PooterWanderState : public MonsterState
{
protected:
    sf::Vector2f targetDirection;
    float directionChangeTimer;
    float directionChangeInterval;

public:
    PooterWanderState();
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "PooterWander"; }
    void ChangeDirection();
};

