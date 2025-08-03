#pragma once
#include "GameObject.h"
class BossMapEnterUI : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/bgblack.png";

	std::string nameId = "graphics/vsnames.png";

	sf::Sprite playerName;
	sf::IntRect playerNameRect = { 0,0,219,60 };
	sf::Sprite playerSprite;
	std::string playerSpriteId = "graphics/playerportrait_01_isaac.png";
	sf::Sprite playerPlate;
	std::string playerPlateId = "graphics/playerspot.png";

	sf::Sprite bossName;
	std::unordered_map<std::string, sf::IntRect> bossNameRect = {
		{"Monstro",{273,13,142,38}},
		{"Dingle", {942,17,126,32}},
	};
	sf::Sprite bossSprite;
	std::unordered_map<std::string, std::string> bossSpriteId = {
		{"Monstro","graphics/portrait_20.0_monstro.png"},
		{"Dingle", "graphics/portrait_261.0_dingle.png"},
	};
	sf::Sprite bossPlate;
	std::string bossPlateId = "graphics/bossspot.png";

	sf::Sprite vsSprite;
	sf::IntRect vsRect = { 13,92,74,41 };

	std::string pickedBoss = "Dingle";

public:
	BossMapEnterUI(const std::string& name = "");
	virtual ~BossMapEnterUI() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPickedBoss(const std::string& str) { pickedBoss = str; }
};

