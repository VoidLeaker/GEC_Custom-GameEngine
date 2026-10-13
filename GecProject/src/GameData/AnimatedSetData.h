#pragma once
#include <string>

struct AnimatedSetData
{
	std::string textureName;
	int numFrames{ 9 };
	int frameWidth; int frameHeight;
	bool isLoop = false;
};