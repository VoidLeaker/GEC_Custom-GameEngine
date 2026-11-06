#include "Enemy.h"
#include "../src/Graphics/GraphicsManager.h"
#include <cmath>

Enemy::Enemy(const std::string& walkAnimation, const CollisionsData& hitbox)
    : m_hitbox(hitbox)
{
    auto& gm = GraphicsManager::GetInstance();
    m_spriteId = gm.createSprite(walkAnimation);
    gm.setPosition(m_spriteId, m_position);
}

Enemy::~Enemy()
{
    if (m_spriteId != 0)
        GraphicsManager::GetInstance().destroySprite(m_spriteId);
}

void Enemy::setPosition(const GraphicsManager::Vec2& pos)
{
    m_position = pos;
    GraphicsManager::GetInstance().setPosition(m_spriteId, m_position);
}

GraphicsManager::Vec2 Enemy::getPosition() const
{
    return m_position;
}

CollisionsData Enemy::getHitbox(float x, float y) const
{
    return CollisionsData(x + m_hitbox.m_posX, y + m_hitbox.m_posY, m_hitbox.m_width, m_hitbox.m_height);
}

bool Enemy::isBlocked(float x, float y, const std::vector<CollisionsData>& blockingHitboxes) const
{
    const CollisionsData hitbox = getHitbox(x, y);
    for (const auto& otherHitbox : blockingHitboxes)
    {
        if (hitbox.intersection(otherHitbox))
        {
            return true;
        }
    }

    return false;
}


void Enemy::update(float dtSeconds, const GraphicsManager::Vec2& playerPosition, const std::vector<CollisionsData>& blockingHitboxes)
{
    auto& gm = GraphicsManager::GetInstance();

	// Calculate the direction vector towards the player
    const float deltaX = playerPosition.x - m_position.x;
    const float deltaY = playerPosition.y - m_position.y;
    const float lengthSquared = (deltaX * deltaX) + (deltaY * deltaY);
    constexpr float stopDistance = 4.f;

    if (lengthSquared > (stopDistance * stopDistance))
    {
        const float length = std::sqrt(lengthSquared);
        const float invLength = 1.f / length;

        m_velocity.x = deltaX * invLength * m_speed;
        m_velocity.y = deltaY * invLength * m_speed;

        if (std::abs(m_velocity.x) > 0.01f)
        {
            m_facingLeft = m_velocity.x < 0.f;
        }
    }
    else
    {
        m_velocity = GraphicsManager::Vec2{ 0.f, 0.f };
    }

    const float newX = m_position.x + m_velocity.x * dtSeconds;
    if (!isBlocked(newX, m_position.y, blockingHitboxes))
    {
        m_position.x = newX;
    }

    const float newY = m_position.y + m_velocity.y * dtSeconds;
    if (!isBlocked(m_position.x, newY, blockingHitboxes))
    {
        m_position.y = newY;
    }

    gm.setFlipped(m_spriteId, m_facingLeft);
    gm.setPosition(m_spriteId, m_position);
}