#pragma once
#include "Monster.h"
#include "SpiderPatrolState.h"
#include "SpiderChargeState.h"
#include "SpiderJumpState.h"


class Spider : public Monster
{
protected:
    SpiderPatrolState patrolState;
    SpiderChargeState chargeState;
    SpiderJumpState jumpState;


public:
    Spider(const std::string& name = "Spider");
    virtual ~Spider() override = default;

    void Reset() override;
    void UseSkill() override;
    //void Update(float dt) override;

    SpiderPatrolState& GetPatrolState() { return patrolState; }
    SpiderChargeState& GetChargeState() { return chargeState; }
    SpiderJumpState& GetJumpState() { return jumpState; }
    void SetInitialState() override;
    sf::FloatRect GetHitBoxMonster() override;

    void ChangeToPatrolState() { ChangeState(&patrolState); }
    void ChangeToChargeState() { ChangeState(&chargeState); }
    void ChangeToJumpState() { ChangeState(&jumpState); }
};

