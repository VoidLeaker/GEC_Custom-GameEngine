#pragma once
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include <vector>
#include <string>

class Enemy
{
public:
	Enemy();
	~Enemy();

	void update(float dtSeconds);
	void draw() {}

	void setPosition(const GraphicsManager::Vec2& pos);
	GraphicsManager::Vec2 getPosition() const;

	CollisionsData getHitbox(float x, float y) const;
	CollisionsData getCurrentHitbox() const { return getHitbox(m_position.x, m_position.y); }

private:

	const std::vector<CollisionsData>* m_walls = nullptr;

	GraphicsManager::SpriteId m_spriteId = 1;
	GraphicsManager::Vec2 m_position{ 300.f, 300.f };
	GraphicsManager::Vec2 m_velocity{ 0.f, 0.f };

	float m_speed = 100.f;
	bool m_facingLeft = false;
	std::string m_currentAnimation = "idle";

};

