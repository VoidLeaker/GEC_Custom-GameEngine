#pragma once
#include <string>

// Holds the data for an animated sprite set, including the texture name, number of frames, frame dimensions, frame duration, and whether the animation is horizontal and loops.

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