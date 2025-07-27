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

    static std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> angleDist;
    std::uniform_real_distribution<float> intervalDist;

public:
    SpiderPatrolState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "SpiderPatrol"; }
    void ChangeDirection();
};