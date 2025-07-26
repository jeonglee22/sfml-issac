#pragma once
#include "Animator.h"
#include "HitBox.h"

struct ItemInventory
{
	int heartCount = 300;
	int coinCount = 0;
	int bombCount = 1;
	int keyCount = 0;
};

class HitBox;
class Tears;
class SceneDev2;
class SceneGame;
class Bomb;

class Isaac : public GameObject
{
protected:
	sf::Sprite body;
	sf::Sprite head;
	Animator bodyAnimator;
	Animator headAnimator;
	ItemInventory inventory;

	std::map<std::string, std::string> headAnimation;
	std::map<std::string, std::string> headTearsAnimation;
	std::map<std::string, std::string> bodyAnimation;

	std::string currentHeadAnimation = "front";
	std::string currentBodyAnimation = "idle";

	std::list<Tears*> tearsList;
	std::list<Tears*> tearsPool;
	std::list<Bomb*> bombsList;
	std::list<Bomb*> bombsPool;

	SceneDev2* sceneDev2 = nullptr;
	SceneGame* sceneGame = nullptr;

	sf::Vector2f velocity = { 0.f, 0.f };
	float speed = 250.f;

	float shootTimer = 0.0f;
	float shootInterval = 0.6f;
	bool wasKeyPressed = false;

	float invincibleTime = 0.0f;
	float invincibleMaxTime = 1.2f;

	bool isHurt = false;
	float currentHurtTime = 0.0;
	float maxHurtTime = 0.4f;

	int maxHP = 300;
	int currentHP = 0;

	bool isDead = false;

	HitBox hitBoxHead;
	HitBox hitBoxBody;

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
	void ItemCollision();
	void HitBoxUpdate();
	void SpritesPositionAtCollision(const sf::Vector2f& beforePos, HitBox* box);

	void TakeDamage(int damage);

	void PlayHeadAnimation(const std::string& animation);
	void PlayHeadTearsAnimation(const std::string& animation);
	void PlayBodyAnimation(const std::string& animation);
	bool IsCurrentHeadAnimation(const std::string& animation) const;
	bool IsCurrentBodyAnimation(const std::string& animation) const;

	void AddItem(Items itemType);

	void InstallBomb();

	HitBox GetHitBoxBody() const { return hitBoxBody; }
	HitBox GetHitBoxHead() const { return hitBoxHead; }
};
