#pragma once
#include "MonsterState.h"

class Monster;

class WanderState : public MonsterState
{
protected:
    sf::Vector2f targetDirection;
    float directionChangeTimer;
    float directionChangeInterval;

public:
    WanderState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "Wander"; }
    void ChangeDirection();

};

