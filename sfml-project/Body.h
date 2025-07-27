#pragma once
#include "Monster.h"
#include "WanderState.h"

class Body : public Monster
{
protected:
    WanderState wanderState;

public:
    Body(const std::string& name = "Body");
    virtual ~Body() override = default;
    void Reset() override;
    void UseSkill() override;
    void SetInitialState() override;
    sf::FloatRect GetHitBoxMonster() override;
};

