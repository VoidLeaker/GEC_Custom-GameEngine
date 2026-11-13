#pragma once
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include "../Entity.h"
#include <vector>
#include <string>

class Enemy : public Entity
{
public:
	Enemy(const std::string& walkAnimation, const CollisionsData& hitbox);
	~Enemy() override = default;

	void update(float dtSeconds, const GraphicsManager::Vec2& playerPosition, const std::vector<CollisionsData>& blockingHitboxes);

	private:
		float m_speed = 100.f;

};

