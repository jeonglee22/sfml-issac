#include "stdafx.h"
#include "Mulligan.h"

Mulligan::Mulligan(const std::string& name)
	:Monster(name, Monsters::Mulligan)
{
}

void Mulligan::Init()
{
    headAnimator.SetTarget(&mulliganHead);
    bodyAnimator.SetTarget(&mulliganBody);
}

void Mulligan::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
    mulliganBody.setPosition(position);
    mulliganHead.setPosition(position.x, position.y - 50.f);

}

//void Monster::SetScale(const sf::Vector2f& s)
//{
//    GameObject::SetScale(s);
//    //mulliganBody.setScale(s);
//    //mulliganHead.setScale(s);
//}

void Mulligan::Draw(sf::RenderWindow& window)
{
    window.draw(mulliganBody);
    window.draw(mulliganHead);
    hitBox.Draw(window);

}

void Mulligan::Reset()
{


    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 2;

    headAnimator.Play("animations/mulligan_idle.csv");
    bodyAnimator.Play("animations/isaac_run_height.csv");

    headAnimator.SetTarget(&mulliganHead);
    bodyAnimator.SetTarget(&mulliganBody);

    SetHP(130);
    SetSpeed(50.0f);
    SetDetectionRange(200.0f);
    SetSkillCooldown(3.0f);
   
    SetScale({ 2.0f, 2.0f });
    mulliganBody.setScale({ 2.0f, 2.0f });
    mulliganHead.setScale({ 2.0f, 2.0f });
    SetOrigin(Origins::MC);

    canUseSkill = true;
    skillTimer = 0.0f;
    skillCooldown = 3.0f;

    SetInitialState();
}

void Mulligan::Update(float dt)
{
    Monster::Update(dt);

    headAnimator.Update(dt);
    bodyAnimator.Update(dt);

    hitBox.UpdateTransform(mulliganHead, mulliganHead.getGlobalBounds());
    hitBox.UpdateTransform(mulliganBody, mulliganBody.getGlobalBounds());
}

void Mulligan::UseSkill()
{
}

void Mulligan::SetInitialState()
{
    ChangeState(&wanderState);
}

sf::FloatRect Mulligan::GetHitBoxMonster()
{
    sf::FloatRect bodyGlobalBounds = mulliganHead.getGlobalBounds();
    return {
        bodyGlobalBounds.left + 25.f,
        bodyGlobalBounds.top + 25.f,
        18.f,
        18.f
    };
}
