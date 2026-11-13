#pragma once

#include "../GameData/EntityComponent.h"
#include <cstdint>
#include <string>
#include <vector>

using EntityId = std::uint32_t;

// Base class for everything in the world. Holds an ID and the components shared by
// all entities (position, velocity, sprite, hitbox). Derived entities add their own
// behaviour and override draw()/getHitbox() when needed.
class Entity
{
public:
	explicit Entity(EntityId id = 0, const CollisionsData& hitbox = CollisionsData());
	virtual ~Entity();
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	EntityId getId() const { return m_id; }
	void setId(EntityId id) { m_id = id; }

	bool isAlive() const { return m_alive; }
	void destroy() { m_alive = false; }

	virtual void draw() {}

	virtual void setPosition(const GraphicsManager::Vec2& pos);
	GraphicsManager::Vec2 getPosition() const { return m_position.position; }

	void setFlipped(bool flipped);

	virtual CollisionsData getHitbox(float x, float y) const;
	CollisionsData getCurrentHitbox() const { return getHitbox(m_position.position.x, m_position.position.y); }
	bool collidesWith(const CollisionsData& other) const { return getCurrentHitbox().intersection(other); }

	void setWalls(const std::vector<CollisionsData>* walls) { m_walls = walls; }
	bool isHittingWall() const { return m_hitWall; }

protected:
	void createSprite(const std::string& animation);
	void syncSprite();

	// Moves by velocity * dt, axis by axis, limited by walls and blocking hitboxes.
	void moveWithCollisions(float dtSeconds, const std::vector<CollisionsData>& blockingHitboxes);

	EntityId m_id = 0;
	bool m_alive = true;

	PositionComponent m_position;
	VelocityComponent m_velocity;
	HitboxComponent m_hitbox;
	SpriteComponent m_sprite;

	bool m_hitWall = false;
	const std::vector<CollisionsData>* m_walls = nullptr;
};
