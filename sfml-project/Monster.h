#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class MonsterState;
class SceneGame;

class Monster : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	Monsters monsterType;

	int currentHP = 0;
	int maxHP = 0;
	bool isDead = false;

	sf::Vector2f velocity;
	float speed = 0.0f;

	float detectionRange;

	sf::Vector2f playerPosition;

	bool canUseSkill;

	float skillTimer;
	float skillCooldown;

	float deadTimer = 0.0f;
	float deadMaxTimer = 1.0f;

	float collisionCooldown = 0.0f;

	float hitFlashTimer = 0.0f;

	MonsterState* currentState;
	HitBox hitBox;
	SceneGame* sceneGame;

public:
	Monster(const std::string& name, Monsters type);
	virtual ~Monster() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override = 0;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void ChangeState(MonsterState* newState);
	std::string GetCurrentStateName() const;

	virtual void TakeDamage(int damage);
	virtual bool IsDead() const { return currentHP <= 0; }
	virtual void UseSkill() = 0;

	Monsters GetMonsterType() const { return monsterType; }
	int GetCurrentHP() const { return currentHP; }
	int GetMaxHP() const { return maxHP; }
	float GetSpeed() const { return speed; }
	sf::Vector2f GetVelocity() const { return velocity; }
	float GetDetectionRange() const { return detectionRange; }

	void SetPlayerPosition(const sf::Vector2f& pos) { playerPosition = pos; }
	sf::Vector2f GetPlayerPosition() const { return playerPosition; }
	void SetVelocity(const sf::Vector2f& vel) { velocity = vel; }

	float GetDistanceToPlayer() const;
	bool CanUseSkill() const { return canUseSkill && skillTimer <= 0; }
	void StartSkillCooldown() { skillTimer = skillCooldown; canUseSkill = false; }

	void SetHP(int hp) { currentHP = maxHP = hp; }
	void SetSpeed(float spd) { speed = spd; }
	void SetDetectionRange(float range) { detectionRange = range; }
	void SetSkillCooldown(float cooldown) { skillCooldown = cooldown; }

	Animator& GetAnimator() { return animator; }
	HitBox& GetHitBox() { return hitBox; }
	virtual sf::FloatRect GetHitBoxMonster() {
		return { 0,0,0,0 };
	}
	sf::RectangleShape GetHitBoxMonsterShape(sf::FloatRect rect)
	{
		sf::RectangleShape shape;
		shape.setPosition(rect.left, rect.top);
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		return shape;
	}
	virtual void SetInitialState() = 0;

	void UpdateSkillTimer(float dt);
	void HitBoxUpdate();
	void SpritesPositionAtCollision(const sf::Vector2f& beforePos, HitBox* box);

	bool WillCollideAt(const sf::Vector2f& testPos);
	sf::Vector2f GetSafeDirection(const sf::Vector2f& currentPos, const sf::Vector2f& currentVel);
	void HandleCollisionByType();
	void HandleHopperJumpCollision();
};

