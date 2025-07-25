#pragma once
#include "MonsterState.h"

class Monster;

class SpiderPatrolState : public MonsterState
{
protected:
    sf::Vector2f targetDirection;
    float directionChangeTimer;
    float directionChangeInterval;
    float pauseTimer;
    float pauseDuration;
    bool isPausing;

    mutable std::random_device rd;
    mutable std::mt19937 gen;

public:
    SpiderPatrolState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "SpiderPatrol"; }
    void ChangeDirection();
};