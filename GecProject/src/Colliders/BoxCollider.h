#pragma once
class CircleCollider;

// Axis-aligned bounding box (AABB). x/y is the top-left corner.
class BoxCollider
{
public:
	float m_x{ 0.f };
	float m_y{ 0.f };
	float m_width{ 0.f };
	float m_height{ 0.f };

	BoxCollider(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f)
		: m_x(x), m_y(y), m_width(width), m_height(height) {}

	bool intersects(const BoxCollider& other) const;
	bool intersects(const CircleCollider& other) const;
};