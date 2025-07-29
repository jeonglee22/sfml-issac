#pragma once
#include "Monster.h"
#include "LarryMoveState.h"

struct BodySegment
{
    sf::Sprite sprite;
    Animator animator;
    sf::Vector2f position;
    int segmentType;

    sf::FloatRect BodyHitBox() const { return sprite.getGlobalBounds(); }
};

class LarryJr : public Monster
{
protected:
    LarryMoveState moveState;
    sf::Vector2f currentDirection;
    float turnTimer;
    float turnInterval;

    static const sf::Vector2f directions[4];
    int currentDirectionIndex;

    std::vector<sf::Vector2f> headTrail;
    float segmentDistance;
    int maxSegments;

public:
    std::vector<BodySegment> bodySegments;

    LarryJr(const std::string& name = "LarryJr");
    virtual ~LarryJr() override = default;
    void Reset() override;
    void UseSkill() override;
    void SetInitialState() override;
    void Draw(sf::RenderWindow& window) override;
    sf::FloatRect GetHitBoxMonster() override;

    void TurnRandomly();
    void TurnAtWall();
    int GetCurrentDirectionIndex() const { return currentDirectionIndex; }
    sf::Vector2f GetCurrentDirection() const { return currentDirection; }
    void SetCurrentDirection(int directionIndex);
    void UpdateTurnTimer(float dt);

    void InitializeBody();
    void UpdateBodyMovement(float dt);
    void DrawBody(sf::RenderWindow& window);
    void RemoveLastSegment();
    int FindTrailIndex(float targetDistance);
    int GetSegmentCount() const { return bodySegments.size(); }
};

