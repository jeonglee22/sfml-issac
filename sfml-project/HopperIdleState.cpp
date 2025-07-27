#include "stdafx.h"
#include "HopperIdleState.h"
#include "Monster.h"
#include "Hopper.h"

std::random_device HopperIdleState::rd;

HopperIdleState::HopperIdleState()
    : idleTimer(0.0f), gen(rd())
{
    idleDuration = 1.0f;
}

void HopperIdleState::Enter(Monster* monster)
{
    idleTimer = 0.0f;
    monster->SetVelocity(sf::Vector2f(0, 0));
    monster->GetAnimator().Play("animations/hopper_idle.csv");
    monster->SetOrigin(Origins::BC);
}

void HopperIdleState::Update(Monster* monster, float dt)
{
    idleTimer += dt;

    if (idleTimer >= idleDuration)
    {
        Hopper* hopper = static_cast<Hopper*>(monster);
        hopper->ChangeToJumpState();
    }
}

void HopperIdleState::Exit(Monster* monster)
{
}