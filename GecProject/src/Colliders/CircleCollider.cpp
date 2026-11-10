#include "CircleCollider.h"
#include "BoxCollider.h"

#include <algorithm>

bool CircleCollider::intersects(const CircleCollider& other) const
{
	// Collide when the distance between centres is less than the sum of radii (squared to avoid sqrt).
	const float dx = other.m_centreX - m_centreX;
	const float dy = other.m_centreY - m_centreY;
	const float radii = m_radius + other.m_radius;
	return dx * dx + dy * dy < radii * radii;
}

bool CircleCollider::intersects(const BoxCollider& other) const
{
	// Closest point on the box to the circle centre.
	const float closestX = std::clamp(m_centreX, other.m_x, other.m_x + other.m_width);
	const float closestY = std::clamp(m_centreY, other.m_y, other.m_y + other.m_height);
	const float dx = m_centreX - closestX;
	const float dy = m_centreY - closestY;
	return dx * dx + dy * dy < m_radius * m_radius;
}
