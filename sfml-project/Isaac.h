#pragma once
#include "Animator.h"
#include "HitBox.h"

struct ItemInventory
{
	int heartCount = 6;
	int coinCount = 0;
	int bombCount = 1;
	int keyCount = 0;
};

class HitBox;
class Tears;
class SceneDev2;
class SceneGame;
class Skill;
class Bomb;
class Skill;
class Chest;

class Isaac : public GameObject
{
protected:
	sf::Sprite body;
	sf::Sprite head;
	std::vector<sf::Sprite> headAdditionals;
	Animator bodyAnimator;
	Animator headAnimator;
	std::vector<Animator> additionalsAnimator;
	ItemInventory inventory;

	std::map<std::string, std::string> headAnimation;
	std::map<std::string, std::string> headTearsAnimation;
	std::map<std::string, std::string> bodyAnimation;
	std::map<std::string, std::string> additonalsAnimation;

	std::string currentHeadAnimation = "front";
	std::string currentBodyAnimation = "idle";

	ChestType chestType;

	bool isShooting = false;

	std::list<Tears*> tearsList;
	std::list<Tears*> tearsPool;
	std::list<Bomb*> bombsList;
	std::list<Bomb*> bombsPool;

	SceneDev2* sceneDev2 = nullptr;
	SceneGame* sceneGame = nullptr;
	//Skill* skill = nullptr;

	sf::Vector2f velocity = { 0.f, 0.f };
	float speed = 250.f;

	float shootTimer = 0.0f;
	float shootInterval = 0.6f;
	bool wasKeyPressed = false;

	float invincibleTime = 0.0f;
	float invincibleMaxTime = 1.2f;

	float itemAnimationTime = 0.0f;
	float itemAnimationMaxTime = 1.5f;

	bool isHurt = false;
	float currentHurtTime = 0.0;
	float maxHurtTime = 0.4f;

	bool isGettingItem = false;

	int maxHP = 6;
	int currentHP = 6;

	int tearCount = 1;

	bool isDead = false;
	bool isBackShoot = false;

	float tearDamage = 35.f;
	float tearSpeed = 250.f;

	HitBox hitBoxHead;
	HitBox hitBoxBody;

	Skill* activeSkill = nullptr;
	std::vector<Skill*> passiveSkill;

	sf::Sprite itemDisplaySprite;
	bool isDisplayingItem = false;
	float itemDisplayTime = 0.0f;
	float itemDisplayMaxTime = 1.5f;
	sf::Vector2f itemDisplayOffset = sf::Vector2f(0.f, -90.f);
	sf::Sprite itemEffectSprite;
	Animator itemEffectAnimator;

public:
	Isaac(const std::string& name = "");
	~Isaac() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void FireTear(const sf::Vector2f& direction);
	void MonsterCollision();
	void ChestCollision();
	void HitBoxUpdate();
	void SpritesPositionAtCollision(const sf::Vector2f& beforePos, HitBox* box);

	void TakeDamage(int damage);

	void PlayHeadAnimation(const std::string& animation);
	void PlayHeadTearsAnimation(const std::string& animation);
	void PlayBodyAnimation(const std::string& animation);
	bool IsCurrentHeadAnimation(const std::string& animation) const;
	bool IsCurrentBodyAnimation(const std::string& animation) const;

	void AddItem(Items itemType);

	void DisplayItem(const std::string& textureId);
	void UpdateItemDisplay(float dt);

	void InstallBomb();

	HitBox GetHitBoxBody() const { return hitBoxBody; }
	HitBox GetHitBoxHead() const { return hitBoxHead; }
	int GetCurrentHP() const { return currentHP; }
	void SetCurrentHP(int hp) { currentHP = hp; }
	int GetMaxHP() const { return maxHP; }
	void SetMaxHP(int hp) { maxHP = hp; }
	float GetInvincibleTime() const { return invincibleTime; }
	void GetiingItem(bool a) { isGettingItem = a; }
	bool IsGetttingItem() { return isGettingItem; }

	void SetActiveSkill(Skill* skill) { this->activeSkill = skill; }
	Skill* GetActiveSkill() { return activeSkill; }
	void SetPassiveSkill(Skill* skill) { passiveSkill.push_back(skill); }

	int GetCoinCount() const { return inventory.coinCount; }
	int GetBombCount() const { return inventory.bombCount; }
	int GetKeyCount() const { return inventory.keyCount; }

	float GetShootInterval() const { return shootInterval; }
	void SetShootInterval(float s) { shootInterval = s; }
	int GetTearCount() const { return tearCount; }
	void SetTearCount(int s) { tearCount = s; }
	int GetTearDamage() const { return tearDamage; }
	void SetTearDamage(float s) { tearDamage = s; }
	float GetTearSpeed() const { return tearSpeed; }
	void SetTearSpeed(float s) { tearSpeed = s; }

	void SetBackShoot(bool b) { isBackShoot = b; }

	void ClampItemCounts();
	void ChangeAnimation();
};
