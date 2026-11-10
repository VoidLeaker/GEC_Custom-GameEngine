#include "BoxCollider.h"
#include "CircleCollider.h"

bool BoxCollider::intersects(const BoxCollider& other) const
{
	return m_x < other.m_x + other.m_width &&
		m_x + m_width > other.m_x &&
		m_y < other.m_y + other.m_height &&
		m_y + m_height > other.m_y;
}

bool BoxCollider::intersects(const CircleCollider& other) const
{
	return other.intersects(*this);
}
