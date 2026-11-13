#include "Enemy.h"
#include "../src/Graphics/GraphicsManager.h"
#include <cmath>

Enemy::Enemy(const std::string& walkAnimation, const CollisionsData& hitbox)
    : Entity(0, hitbox)
{
    m_position.position = GraphicsManager::Vec2{ 300.f, 300.f };
    createSprite(walkAnimation);
}

void Enemy::update(float dtSeconds, const GraphicsManager::Vec2& playerPosition, const std::vector<CollisionsData>& blockingHitboxes)
{
	// Calculate the direction vector towards the player
	const float deltaX = playerPosition.x - m_position.position.x;
	const float deltaY = playerPosition.y - m_position.position.y;
    const float lengthSquared = (deltaX * deltaX) + (deltaY * deltaY);
    constexpr float stopDistance = 4.f;

    if (lengthSquared > (stopDistance * stopDistance))
    {
        const float length = std::sqrt(lengthSquared);
        const float invLength = 1.f / length;

        m_velocity.velocity.x = deltaX * invLength * m_speed;
        m_velocity.velocity.y = deltaY * invLength * m_speed;

        if (std::abs(m_velocity.velocity.x) > 0.01f)
        {
            m_sprite.facingLeft = m_velocity.velocity.x < 0.f;
        }
    }
    else
    {
        m_velocity.velocity = GraphicsManager::Vec2{ 0.f, 0.f };
    }

    moveWithCollisions(dtSeconds, blockingHitboxes);
    syncSprite();
}