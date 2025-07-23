#pragma once
#include "MonsterState.h"

class Monster;

class SpiderJumpState : public MonsterState
{
protected:
    sf::Vector2f startPosition;
    sf::Vector2f targetPosition;
    sf::Vector2f jumpVelocity;
    float jumpSpeed;

public:
    SpiderJumpState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "SpiderJump"; }

    void SetTarget(const sf::Vector2f& target) { targetPosition = target; }
};

