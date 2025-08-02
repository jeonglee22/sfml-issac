#pragma once
#include "MonsterState.h"
class MulliganDeathState : public MonsterState
{
protected:
    float deathTimer;
    float faceSwellDuration;
    float explosionDuration;

    bool faceSwelled;
    bool exploded;

public:
    MulliganDeathState();

    void Enter(Monster* monster) override;
    void Update(Monster* monster, float dt) override;
    void Exit(Monster* monster) override;
    std::string GetStateName() const override { return "MulliganDeath"; }
    void SpawnFlies(Monster* monster);
};

