#pragma once
#include "Monster.h"
#include "HopperIdleState.h"
#include "HopperJumpState.h"

class SceneGame;

class Hopper : public Monster
{
protected:
    HopperIdleState idleState;
    HopperJumpState jumpState;

    SceneGame* sceneGame;

public:
    Hopper(const std::string& name = "Hopper");
    virtual ~Hopper() override = default;
    void Reset() override;
    void UseSkill() override;
    void SetInitialState() override;
    //sf::FloatRect GetHitBoxMonster() override;

    void ChangeToIdleState() { ChangeState(&idleState); }
    void ChangeToJumpState() { ChangeState(&jumpState); }

    sf::FloatRect GetHitBoxMonster()
    {
        return
        {
            position.x - 10.f,
            position.y - 10.f,
            20.f,
            20.f 
        };
    }
};

