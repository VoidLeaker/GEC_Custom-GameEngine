#pragma once
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include <string>

class BaseProjectiles
{
public:
	BaseProjectiles(const std::string& animation, const CollisionsData& hitbox);
	~BaseProjectiles();
	BaseProjectiles(const BaseProjectiles&) = delete;
	BaseProjectiles& operator=(const BaseProjectiles&) = delete;

	void setPosition(const GraphicsManager::Vec2& pos);
	GraphicsManager::Vec2 getPosition() const { return m_position; }
	void setFlipped(bool flipped);

	CollisionsData getCurrentHitbox() const;
	bool collidesWith(const CollisionsData& other) const { return getCurrentHitbox().intersection(other); }

private:
	GraphicsManager::SpriteId m_spriteId = 0;
	CollisionsData m_hitbox;
	GraphicsManager::Vec2 m_position{ 0.f, 0.f };
};

