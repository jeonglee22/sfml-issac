#pragma once
#include "Monster.h"
#include "MonstroIdleState.h"
#include "MonstroJumpChargeState.h"
#include "MonstroJumpingState.h"
#include "MonstroLandingState.h"
#include "MonstroFireState.h"
#include "MonstroSmallJumpState.h"
#include "EnemyTears.h"

class Monstro : public Monster
{
protected:
    MonstroIdleState idleState;
    MonstroJumpChargeState jumpChargeState;
    MonstroJumpingState jumpingState;
    MonstroLandingState landingState;
    MonstroFireState fireState;
    MonstroSmallJumpState smallJumpState;

    std::list<EnemyTears*> EnemyTearsList;
    std::list<EnemyTears*> EnemyTearsPool;
    float tearsSpeed = 150.0f;
    int tearsDamage = 1;

    sf::Vector2f jumpTarget;
    sf::Vector2f jumpStartPos;
    float jumpProgress = 0.0f;
    bool isInAir = false;

public:
    Monstro(const std::string& name = "Monstro");
    virtual ~Monstro() override = default;

    sf::FloatRect GetHitBoxMonster() override;

    void ChangeToIdleState() { ChangeState(&idleState); }
    void ChangeToJumpChargeState() { ChangeState(&jumpChargeState); }
    void ChangeToJumpingState() { ChangeState(&jumpingState); }
    void ChangeToLandingState() { ChangeState(&landingState); }
    void ChangeToFireState() { ChangeState(&fireState); }
    void ChangeToSmallJumpState() { ChangeState(&smallJumpState); }

    void Reset() override;
    void UseSkill() override;
    void SetInitialState() override;
    void Update(float dt) override;

    void FireTear(const sf::Vector2f& direction);
    void FireBloodSplatter();
    void FireCoughAttack();
    void UpdateTears(float dt);

    // 점프 관련
    void SetJumpTarget(const sf::Vector2f& target);
    sf::Vector2f GetJumpTarget() const { return jumpTarget; }
    sf::Vector2f GetJumpStartPos() const { return jumpStartPos; }
    void SetJumpProgress(float progress) { jumpProgress = progress; }
    float GetJumpProgress() const { return jumpProgress; }

    void SetInAir(bool inAir) { isInAir = inAir; }
    bool IsInAir() const { return isInAir; }

    const std::list<EnemyTears*>& GetTears() const { return EnemyTearsList; }
};

