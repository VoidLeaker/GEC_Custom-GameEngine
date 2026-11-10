#pragma once
class BoxCollider;

// Circle defined by its centre and radius.
class CircleCollider
{
public:
	float m_centreX{ 0.f };
	float m_centreY{ 0.f };
	float m_radius{ 0.f };

	CircleCollider(float centreX = 0.f, float centreY = 0.f, float radius = 0.f)
		: m_centreX(centreX), m_centreY(centreY), m_radius(radius) {}

	bool intersects(const CircleCollider& other) const;
	bool intersects(const BoxCollider& other) const;
};