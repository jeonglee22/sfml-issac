#pragma once
#include "MonsterState.h"
#include "Monster.h"
#include "WanderState.h"

class IdleState : public MonsterState
{
protected:
    float idleTime;
    float maxIdleTime;

public:
    IdleState() : idleTime(0.0f), maxIdleTime(2.0f) {}

    void Enter(Monster* monster) override
    {
        idleTime = 0.0f;
        monster->SetVelocity(sf::Vector2f(0, 0));
    }

    void Update(Monster* monster, float dt) override
    {
        idleTime += dt;
    }

    void Exit(Monster* monster) override { }

    std::string GetStateName() const override { return "Idle"; }
};

