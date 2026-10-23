#include "CollisionsData.h"

bool CollisionsData::intersection(const CollisionsData& other) const
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
