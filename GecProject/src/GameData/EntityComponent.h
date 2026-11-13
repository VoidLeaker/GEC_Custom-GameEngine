#pragma once
#include "../Graphics/GraphicsManager.h"
#include "CollisionsData.h"

struct PositionComponent
{
	GraphicsManager::Vec2 position{ 0.f, 0.f };
};

struct VelocityComponent
{
	GraphicsManager::Vec2 velocity{ 0.f, 0.f };
	float speed{ 0.f };
};

struct ScaleComponent
{
	GraphicsManager::Vec2 scale{ 1.f, 1.f };
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

struct HitboxComponent
{
	CollisionsData localHitbox;
};

struct SpriteComponent
{
	GraphicsManager::SpriteId spriteId{ 0 };
	bool facingLeft{ false };
};
