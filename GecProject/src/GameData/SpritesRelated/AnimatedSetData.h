#pragma once
#include <string>

struct AnimatedSetData
{
	std::string textureName;
	int numFrames{ 1 };
	int frameWidth{ 0 };
	int frameHeight{ 0 };
	float frameSeconds{ 0.1f };
	bool isHorizontal{ false };
	bool isLoop{ true };
};