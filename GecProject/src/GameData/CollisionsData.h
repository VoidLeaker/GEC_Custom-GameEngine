#pragma once

#include <vector>

#include "../Colliders/BoxCollider.h"
#include "../Colliders/CircleCollider.h"

// Holds the data for a hitbox or collision shape, including its position, size, and shape type (box or circle). 
// Provides methods for checking intersection with other collision shapes and limiting movement based on obstacles.

class CollisionsData
{
public:
	enum class Shape { Box, Circle };

	// For circles, the bounds (pos/width/height) are the circle's bounding square; width is the diameter.
	Shape m_shape{ Shape::Box };

	float m_posX{ 0.f };
	float m_posY{ 0.f };

	float m_width{ 0.f };
	float m_height{ 0.f };

	CollisionsData(float posX = 0.f, float posY = 0.f, float width = 0.f, float height = 0.f, Shape shape = Shape::Box)
		: m_shape(shape), m_posX(posX), m_posY(posY), m_width(width), m_height(height) {}

	static CollisionsData makeCircle(float centreX, float centreY, float radius);

	// Converts to a BoxCollider or CircleCollider for collision detection.
	BoxCollider toBox() const;
	CircleCollider toCircle() const;

	bool intersection(const CollisionsData& other) const;
	CollisionsData moved(float distance, bool horizontal) const;

	// Largest movement (up to distance) along one axis that does not run into the obstacle. Used when a circle is involved.
	float limitMovementSwept(float distance, bool horizontal, const CollisionsData& obstacle) const;

	float limitMovement(float distance, bool horizontal, const std::vector<CollisionsData>& obstacles) const;
};

