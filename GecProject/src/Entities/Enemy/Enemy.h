#pragma once
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include <vector>
#include <string>

class Enemy
{
public:
	Enemy(const std::string& walkAnimation, const CollisionsData& hitbox);
	~Enemy();
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;

	void update(float dtSeconds, const GraphicsManager::Vec2& playerPosition, const std::vector<CollisionsData>& blockingHitboxes);
	void draw() {}

	void setPosition(const GraphicsManager::Vec2& pos);
	GraphicsManager::Vec2 getPosition() const;

	CollisionsData getHitbox(float x, float y) const;
	CollisionsData getCurrentHitbox() const { return getHitbox(m_position.x, m_position.y); }

	void setWalls(const std::vector<CollisionsData>* walls) { m_walls = walls; }
	bool isHittingWall() const { return m_hitWall; }

private:
	bool m_hitWall = false;
	const std::vector<CollisionsData>* m_walls = nullptr;

	GraphicsManager::SpriteId m_spriteId = 0;
	CollisionsData m_hitbox;
	GraphicsManager::Vec2 m_position{ 300.f, 300.f };
	GraphicsManager::Vec2 m_velocity{ 0.f, 0.f };

	float m_speed = 100.f;
	bool m_facingLeft = false;

};

