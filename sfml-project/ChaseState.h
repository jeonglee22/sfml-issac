#pragma once
#include "MonsterState.h"

class Monster;

class ChaseState : public MonsterState
{
protected:
    sf::Vector2f startPosition;
    sf::Vector2f targetPosition;
    sf::Vector2f chaseVelocity;

    float chaseSpeed = 80.f;

public:
    ChaseState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "Chaser"; }

};

