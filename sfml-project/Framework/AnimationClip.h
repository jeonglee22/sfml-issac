#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	//PingPong,
};

struct AnimationFrame
{
	std::string texId;
	sf::IntRect texCoord;
	sf::Vector2f texOrigin;

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord, const sf::Vector2f& texOrigin) : texId(texId), texCoord(texCoord), texOrigin(texOrigin) {}
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
	int fps = 30;

	std::vector<AnimationFrame> frames;

	bool loadFromFile(const std::string& filePath);
};

