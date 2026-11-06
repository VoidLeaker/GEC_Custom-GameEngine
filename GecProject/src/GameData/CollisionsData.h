#pragma once

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
};