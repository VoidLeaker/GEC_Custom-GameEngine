#include "Enemy.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/AnimatedSetData.h"
#include <cmath>

Enemy::Enemy()
{
	auto& gm = GraphicsManager::GetInstance();

    gm.loadTexture("knight_idle", "Assets/Textures/SL_Knight/idle_combined.png");
    gm.loadTexture("knight_walk", "Assets/Textures/SL_Knight/run_combined.png");

    AnimatedSetData idleSet;
    idleSet.textureName = "knight_idle";
    idleSet.numFrames = 8;
    idleSet.frameWidth = 128;
    idleSet.frameHeight = 64;
    idleSet.frameSeconds = 0.12f;
    idleSet.isHorizontal = false;
    idleSet.isLoop = true;

    AnimatedSetData walkSet;
    walkSet.textureName = "knight_walk";
    walkSet.numFrames = 8;
    walkSet.frameWidth = 128;
    walkSet.frameHeight = 64;
    walkSet.frameSeconds = 0.10f;
    walkSet.isHorizontal = false;
    walkSet.isLoop = true;

    gm.addAnimationSet("idle", idleSet);
    gm.addAnimationSet("walk", walkSet);

    m_spriteId = gm.createSprite("idle");
    gm.setPosition(m_spriteId, m_position);
    gm.setAnimation(m_spriteId, "idle");
}

Enemy::~Enemy()
{
    if (m_spriteId != 1)
        GraphicsManager::GetInstance().destroySprite(m_spriteId);
}

CollisionsData Enemy::getHitbox(float x, float y) const
{
    constexpr float offsetX = 48.f;
    constexpr float offsetY = 24.f;
    constexpr float width = 32.f;
    constexpr float height = 36.f;
    return CollisionsData(x + offsetX, y + offsetY, width, height);
}


void Enemy::update(float dtSeconds, const GraphicsManager::Vec2& playerPosition)
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

    m_position.x += m_velocity.x * dtSeconds;
    m_position.y += m_velocity.y * dtSeconds;

    std::string desiredAnimation = "idle";

    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        desiredAnimation = "walk";
    }

    if (desiredAnimation != m_currentAnimation)
    {
        m_currentAnimation = desiredAnimation;
        gm.setAnimation(m_spriteId, desiredAnimation);
    }

    gm.setFlipped(m_spriteId, m_facingLeft);
    gm.setPosition(m_spriteId, m_position);
}