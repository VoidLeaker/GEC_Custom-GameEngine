#pragma once

#include <vector>

class CollisionsData
{
public:
	float m_posX{ 0.f };
	float m_posY{ 0.f };

	float m_width{ 0.f };
	float m_height{ 0.f };

	CollisionsData(float posX = 0.f, float posY = 0.f, float width = 0.f, float height = 0.f)
		: m_posX(posX), m_posY(posY), m_width(width), m_height(height) {}

	bool intersection(const CollisionsData& other) const
	{
		if (m_posX < other.m_posX + other.m_width &&
			m_posX + m_width > other.m_posX &&
			m_posY < other.m_posY + other.m_height &&
			m_posY + m_height > other.m_posY)
		{
			return true;
		}
		return false;
	}

	float limitMovement(float distance, bool horizontal, const std::vector<CollisionsData>& obstacles) const
	{
		const float start = horizontal ? m_posX : m_posY;
		const float size = horizontal ? m_width : m_height;
		const float crossStart = horizontal ? m_posY : m_posX;
		const float crossSize = horizontal ? m_height : m_width;

		for (const auto& obstacle : obstacles)
		{
			const float obstacleStart = horizontal ? obstacle.m_posX : obstacle.m_posY;
			const float obstacleSize = horizontal ? obstacle.m_width : obstacle.m_height;
			const float obstacleCrossStart = horizontal ? obstacle.m_posY : obstacle.m_posX;
			const float obstacleCrossSize = horizontal ? obstacle.m_height : obstacle.m_width;

			if (crossStart >= obstacleCrossStart + obstacleCrossSize || crossStart + crossSize <= obstacleCrossStart)
				continue;

			if (distance > 0.f && start + size <= obstacleStart)
			{
				const float gap = obstacleStart - (start + size);
				if (distance > gap)
					distance = gap;
			}
			else if (distance < 0.f && start >= obstacleStart + obstacleSize)
			{
				const float gap = obstacleStart + obstacleSize - start;
				if (distance < gap)
					distance = gap;
			}
		}
		return distance;
	}
};