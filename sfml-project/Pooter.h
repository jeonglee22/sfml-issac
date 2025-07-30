#pragma once
#include "Monster.h"
#include "PooterWanderState.h"
#include "PooterFireState.h"
#include "EnemyTears.h"

class Pooter : public Monster
{
protected:
    PooterWanderState wanderState;
    PooterFireState fireState;
    std::list<EnemyTears*> EnemyTearsList;
    std::list<EnemyTears*> EnemyTearsPool;
    float tearsSpeed = 150.0f;
    int tearsDamage = 1;

public:
    Pooter(const std::string& name = "Pooter");
    virtual ~Pooter() override = default;

    void Reset() override;
    void UseSkill() override;
    void SetInitialState() override;
    sf::FloatRect GetHitBoxMonster() override;

    void ChangeToWanderState() { ChangeState(&wanderState); }
    void ChangeToFireState() { ChangeState(&fireState); }

    void FireProjectile(const sf::Vector2f& direction);
    void UpdateProjectiles(float dt);

    PooterWanderState& GetWanderState() { return wanderState; }
    PooterFireState& GetShootState() { return fireState; }
    const std::list<EnemyTears*>& GetProjectiles() const { return EnemyTearsList; }




};

