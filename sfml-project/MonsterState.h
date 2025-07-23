#pragma once

class Monster;

class MonsterState {
public:
    virtual ~MonsterState() = default;
    virtual void Enter(Monster* monster) = 0;
    virtual void Update(Monster* monster, float dt) = 0;
    virtual void Exit(Monster* monster) = 0;
    virtual std::string GetStateName() const = 0;
};

