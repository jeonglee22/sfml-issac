#pragma once
#include "Monster.h"

class SpiderPatrolState;
class SpiderChargeState;
class SpiderJumpState;

class Spider : public Monster
{
public:
    static SpiderPatrolState patrolState;
    static SpiderChargeState chargeState;
    static SpiderJumpState jumpState;

    Spider(const std::string& name = "Spider");
    virtual ~Spider() override = default;

    void Reset() override;
    void UseSkill() override;
    void OnUpdate(float dt) override;

    static SpiderPatrolState& GetPatrolState() { return patrolState; }
    static SpiderChargeState& GetChargeState() { return chargeState; }
    static SpiderJumpState& GetJumpState() { return jumpState; }
    void SetInitialState() override;
    sf::FloatRect GetHitBoxMonster() override;
};

