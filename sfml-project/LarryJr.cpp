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
    std::cout << "LarryJr::Reset() called!" << std::endl;

    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 3;
    SetHP(880);
    SetSpeed(200.0f);
    SetDetectionRange(500.0f);
    SetSkillCooldown(0.0f);
    animator.Play("animations/boss_larry_jr_head_side.csv");
    SetScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    segmentDistance = 70.0f;
    maxSegments = 5;
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
    std::cout << "SetInitialState called!" << std::endl;

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
    static int callCount = 0;
    callCount++;
    std::cout << "InitializeBody called! Count: " << callCount << std::endl;

    bodySegments.clear();
    headTrail.clear();

    maxSegments = 5;

    // 바디가 제자리를 찾을 수 있도록 충분한 headTrail 미리 생성
    int totalTrailPoints = 1000; // 충분히 많이
    for (int i = 0; i < totalTrailPoints; i++)
    {
        sf::Vector2f trailPos = position - currentDirection * (float)i * 200.0f; // 3픽셀 간격
        headTrail.push_back(trailPos);
    }

    headTrail.clear();

    // 바디 세그먼트 생성
    for (int i = 1; i < maxSegments; i++)
    {
        BodySegment segment;
        segment.segmentType = 1;
        segment.position = position - currentDirection * segmentDistance * (float)i;
        bodySegments.push_back(segment);
    }

    // 애니메이터 설정
    for (int i = 0; i < bodySegments.size(); i++)
    {
        bodySegments[i].animator.SetTarget(&bodySegments[i].sprite);
        bodySegments[i].animator.Play("animations/boss_larry_jr_body1.csv");

        bodySegments[i].sprite.setPosition(bodySegments[i].position);
        bodySegments[i].sprite.setScale({ 2.0f, 2.0f });
        Utils::SetOrigin(bodySegments[i].sprite, Origins::MC);
    }

    std::cout << "HeadTrail initialized with " << headTrail.size() << " points" << std::endl;
}

void LarryJr::UpdateBodyMovement(float dt)
{
    static sf::Vector2f lastHeadPos = position;
    static int frameCount = 0;
    frameCount++;

    headTrail.insert(headTrail.begin(), position);

    if (headTrail.size() > 350.f)
    {
        headTrail.pop_back();
    }

    for (int i = 0; i < bodySegments.size(); i++)
    {
        if (frameCount < 50) // 처음 50프레임 동안은 직접 계산
        {
            bodySegments[i].position = position - currentDirection * segmentDistance * (float)(i + 1);
        }
        else // 그 후에는 trail 사용
        {
            int trailIndex = (i + 1) * 10;
            if (trailIndex < headTrail.size())
            {
                bodySegments[i].position = headTrail[trailIndex];
            }
        }

        bodySegments[i].sprite.setPosition(bodySegments[i].position);
        bodySegments[i].animator.Update(dt);
    }

    lastHeadPos = position;
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
    for (int i = bodySegments.size() - 1; i >= 0; i--)
    {
        window.draw(bodySegments[i].sprite);
    }
}

void LarryJr::RemoveLastSegment()
{
    if (!bodySegments.empty())
    {
        bodySegments.pop_back();
        maxSegments--;
    }
}
