#pragma once
#include "MonsterState.h"
class HopperJumpState : public MonsterState
{
protected:
    sf::Vector2f jumpDirection;
    float jumpDistance;
    sf::Vector2f startPosition;
    sf::Vector2f targetPosition;
    float jumpSpeed;

    static std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> angleDist;
    std::uniform_real_distribution<float> distanceDist;

public:
    HopperJumpState();
    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "HopperJump"; }
};

