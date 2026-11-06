#pragma once
#include <SFML/Graphics.hpp>

struct PositionComponent
{
	sf::Vector2f position{ 0.f, 0.f };
};

struct VelocityComponent
{
	sf::Vector2f velocity{ 0.f, 0.f };
};

struct ScaleComponent
{
	sf::Vector2f scale{ 1.f, 1.f };
};

struct RotationComponent
{
	float rotation{ 0.f };
};

struct HealthComponent
{
	int maxhealth{ 100 };
	int currenthealth{ 100 };
};