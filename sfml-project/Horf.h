#pragma once
#include "Monster.h"
#include "IdleState.h"
#include "HorfFireState.h"
#include "EnemyTears.h"

class Horf : public Monster
{
protected:
    IdleState idleState;
    HorfFireState fireState;

    std::list<EnemyTears*> EnemyTearsList;
    std::list<EnemyTears*> EnemyTearsPool;

    float tearsSpeed = 300.0f;
    int tearsDamage = 1;

public:
    Horf(const std::string& name = "Horf");
    virtual ~Horf() override = default;

    void Reset() override;
    void UseSkill() override;
    void SetInitialState() override;
    sf::FloatRect GetHitBoxMonster() override;

    void ChangeToIdleState() { ChangeState(&idleState); }
    void ChangeToFireState() { ChangeState(&fireState); }

    void FireProjectile(const sf::Vector2f& direction);
    void UpdateTears(float dt);

    IdleState& GetIdleState() { return idleState; }
    HorfFireState& GetShootState() { return fireState; }

    const std::list<EnemyTears*>& GetProjectiles() const { return EnemyTearsList; }
};

