#include "stdafx.h"
#include "LarryJr.h"

const sf::Vector2f LarryJr::directions[4] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

LarryJr::LarryJr(const std::string& name)
    : Monster(name, Monsters::LarryJr)
{
    currentDirectionIndex = 1;
    currentDirection = directions[currentDirectionIndex];
    turnTimer = 0.0f;
    turnInterval = 3.0f;
}

void LarryJr::Reset()
{
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 3;
    SetHP(400);
    SetSpeed(120.0f);
    SetDetectionRange(500.0f);
    SetSkillCooldown(0.0f);
    animator.Play("animations/boss_larry_jr_head_side.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    segmentDistance = 150.0f;
    maxSegments = 4;
    InitializeBody();

    currentDirectionIndex = Utils::RandomRange(0, 3);
    currentDirection = directions[currentDirectionIndex];
    turnTimer = 0.0f;

    SetInitialState();
}

void LarryJr::UseSkill()
{
}

void LarryJr::SetInitialState()
{
    ChangeState(&moveState);
}

sf::FloatRect LarryJr::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = body.getGlobalBounds();
    return
    {
        bodyGlobalBounds.left + 20.f,
        bodyGlobalBounds.top + 20.f,
        30.f,
        30.f
    };
}

void LarryJr::TurnRandomly()
{

    int turnDirection = Utils::RandomRange(0, 1) == 0 ? -1 : 1;
    currentDirectionIndex = (currentDirectionIndex + turnDirection + 4) % 4;
    currentDirection = directions[currentDirectionIndex];
}

void LarryJr::TurnAtWall()
{
    int turnDirection = Utils::RandomRange(0, 1) == 0 ? -1 : 1;
    currentDirectionIndex = (currentDirectionIndex + turnDirection + 4) % 4;
    currentDirection = directions[currentDirectionIndex];
}

void LarryJr::SetCurrentDirection(int directionIndex)
{
    currentDirectionIndex = directionIndex;
    currentDirection = directions[currentDirectionIndex];
}

void LarryJr::UpdateTurnTimer(float dt)
{
    turnTimer += dt;
    if (turnTimer >= turnInterval)
    {
        TurnRandomly();
        turnTimer = 0.0f;
        turnInterval = Utils::RandomRange(2.0f, 5.0f);
    }
}

void LarryJr::InitializeBody()
{
    bodySegments.clear();
    headTrail.clear();

    maxSegments = 4;

    for (int i = 0; i < maxSegments + 5; i++)
    {
        headTrail.push_back(position);
    }

    for (int i = 1; i < maxSegments; i++)
    {
        BodySegment segment;

        segment.segmentType = 1;

        segment.animator.SetTarget(&segment.sprite);
        segment.animator.Play("animations/boss_larry_jr_body1.csv");

        segment.position = position - currentDirection * segmentDistance * (i + 1.0f);
        segment.sprite.setPosition(segment.position);
        segment.sprite.setScale({ 2.0f, 2.0f });
        Utils::SetOrigin(segment.sprite, Origins::MC);

        bodySegments.push_back(segment);
    }
}

void LarryJr::UpdateBodyMovement(float dt)
{
    headTrail.insert(headTrail.begin(), position);

    if (headTrail.size() > maxSegments * 3 + 10)
    {
        headTrail.pop_back();
    }

    for (int i = 0; i < bodySegments.size(); i++)
    {
        int trailIndex = FindTrailIndex(segmentDistance * (i + 1));

        if (trailIndex < headTrail.size())
        {
            bodySegments[i].position = headTrail[trailIndex];
            bodySegments[i].sprite.setPosition(bodySegments[i].position);
        }

        bodySegments[i].animator.Update(dt);
    }
}

int LarryJr::FindTrailIndex(float targetDistance)
{
    float currentDistance = 0.0f;

    for (int i = 1; i < headTrail.size(); i++)
    {
        sf::Vector2f diff = headTrail[i - 1] - headTrail[i];
        currentDistance += std::sqrt(diff.x * diff.x + diff.y * diff.y);

        if (currentDistance >= targetDistance)
        {
            return i;
        }
    }

    return headTrail.size() - 1;
}

void LarryJr::Draw(sf::RenderWindow& window)
{
    DrawBody(window);
    Monster::Draw(window);
}

void LarryJr::DrawBody(sf::RenderWindow& window)
{
    for (int i = bodySegments.size() - 1; i >= 0; i--) {
        window.draw(bodySegments[i].sprite);
    }
}

void LarryJr::RemoveLastSegment()
{
    if (!bodySegments.empty()) {
        bodySegments.pop_back();
        maxSegments--;
    }
}
