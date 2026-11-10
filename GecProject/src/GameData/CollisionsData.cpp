#include "CollisionsData.h"

CollisionsData CollisionsData::makeCircle(float centreX, float centreY, float radius)
{
	return CollisionsData(centreX - radius, centreY - radius, radius * 2.f, radius * 2.f, Shape::Circle);
}

BoxCollider CollisionsData::toBox() const
{
	return BoxCollider(m_posX, m_posY, m_width, m_height);
}

CircleCollider CollisionsData::toCircle() const
{
	return CircleCollider(m_posX + m_width * 0.5f, m_posY + m_height * 0.5f, m_width * 0.5f);
}

bool CollisionsData::intersection(const CollisionsData& other) const
{
	if (m_shape == Shape::Box)
	{
		return other.m_shape == Shape::Box ? toBox().intersects(other.toBox()) : toBox().intersects(other.toCircle());
	}
	return other.m_shape == Shape::Box ? toCircle().intersects(other.toBox()) : toCircle().intersects(other.toCircle());
}

CollisionsData CollisionsData::moved(float distance, bool horizontal) const
{
	CollisionsData result = *this;
	(horizontal ? result.m_posX : result.m_posY) += distance;
	return result;
}

float CollisionsData::limitMovementSwept(float distance, bool horizontal, const CollisionsData& obstacle) const
{
	if (intersection(obstacle) || !moved(distance, horizontal).intersection(obstacle))
		return distance;

	float free = 0.f;
	float blocked = distance;
	for (int i = 0; i < 16; ++i)
	{
		const float mid = (free + blocked) * 0.5f;
		if (moved(mid, horizontal).intersection(obstacle))
			blocked = mid;
		else
			free = mid;
	}
	return free;
}

float CollisionsData::limitMovement(float distance, bool horizontal, const std::vector<CollisionsData>& obstacles) const
{
	const float start = horizontal ? m_posX : m_posY;
	const float size = horizontal ? m_width : m_height;
	const float crossStart = horizontal ? m_posY : m_posX;
	const float crossSize = horizontal ? m_height : m_width;

	for (const auto& obstacle : obstacles)
	{
		if (m_shape == Shape::Circle || obstacle.m_shape == Shape::Circle)
		{
			distance = limitMovementSwept(distance, horizontal, obstacle);
			continue;
		}

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
