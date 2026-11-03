#include "Enemy.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/SpritesRelated/AnimatedSetData.h"
#include <cmath>

Enemy::Enemy()
{
	auto& gm = GraphicsManager::GetInstance();

    gm.loadTexture("bluegolem_walk", "Assets/Textures/Monster/BlueGolem-Walk.png");

    AnimatedSetData walkSet;
    walkSet.textureName = "bluegolem_walk";
    walkSet.numFrames = 10;
    walkSet.frameWidth = 90;
    walkSet.frameHeight = 64;
    walkSet.frameSeconds = 0.10f;
    walkSet.isHorizontal = true;
    walkSet.isLoop = true;

    gm.addAnimationSet("enemy_walk", walkSet);

    m_spriteId = gm.createSprite("enemy_walk");
    gm.setPosition(m_spriteId, m_position);
    gm.setAnimation(m_spriteId, "enemy_walk");
}

Enemy::~Enemy()
{
    if (m_spriteId != 1)
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
    constexpr float offsetX = 48.f;
    constexpr float offsetY = 24.f;
    constexpr float width = 32.f;
    constexpr float height = 36.f;
    return CollisionsData(x + offsetX, y + offsetY, width, height);
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

    std::string desiredAnimation = "enemy_walk";

    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        desiredAnimation = "enemy_walk";
    }

    if (desiredAnimation != m_currentAnimation)
    {
        m_currentAnimation = desiredAnimation;
        gm.setAnimation(m_spriteId, desiredAnimation);
    }

    gm.setFlipped(m_spriteId, m_facingLeft);
    gm.setPosition(m_spriteId, m_position);
}