#include "Player.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/AnimatedSetData.h"

Player::Player()
{
    INPUT_MAN.addListener(this);

    auto& gm = GraphicsManager::GetInstance();

    gm.loadTexture("knight_idle", "Assets/Textures/SL_Knight/idle_combined.png");
    gm.loadTexture("knight_attack_right", "Assets/Textures/SL_Knight/attack_right_combined.png");
    gm.loadTexture("knight_attack_left", "Assets/Textures/SL_Knight/attack_left_combined.png");
    gm.loadTexture("knight_walk", "Assets/Textures/SL_Knight/run_combined.png");

    AnimatedSetData idleSet;
    idleSet.textureName = "knight_idle";
    idleSet.numFrames = 8;
    idleSet.frameWidth = 128;
    idleSet.frameHeight = 64;
    idleSet.frameSeconds = 0.12f;
    idleSet.isHorizontal = false;
    idleSet.isLoop = true;

    AnimatedSetData attackSet;
    attackSet.textureName = "knight_attack_right";
    attackSet.numFrames = 6;
    attackSet.frameWidth = 128;
    attackSet.frameHeight = 64;
    attackSet.frameSeconds = 0.08f;
    attackSet.isHorizontal = false;
    attackSet.isLoop = false;

    AnimatedSetData attackLeftSet = attackSet;
    attackLeftSet.textureName = "knight_attack_left";

    AnimatedSetData walkSet;
    walkSet.textureName = "knight_walk";
    walkSet.numFrames = 8;
    walkSet.frameWidth = 128;
    walkSet.frameHeight = 64;
    walkSet.frameSeconds = 0.10f;
    walkSet.isHorizontal = false;
    walkSet.isLoop = true;

    gm.addAnimationSet("idle", idleSet);
    gm.addAnimationSet("attack", attackSet);
    gm.addAnimationSet("attackLeft", attackLeftSet);
    gm.addAnimationSet("walk", walkSet);

    m_spriteId = gm.createSprite("idle");
    gm.setPosition(m_spriteId, m_position);
    gm.setAnimation(m_spriteId, "idle");
}

Player::~Player()
{
    INPUT_MAN.removeListener(this);
    if (m_spriteId != 0)
        GraphicsManager::GetInstance().destroySprite(m_spriteId);
}

void Player::handleInput(InputAction action)
{
    if (action == InputAction::eLeftMouseClick)
    {
        if (!m_mouseHeld && !m_attacking)
        {
            m_attacking = true;
            m_attackTimer = m_attackDuration;
        }
        m_mouseHeld = true;
        return;
    }
    m_mouseHeld = false;

    switch (action)
    {
    case InputAction::eMoveUp:
        m_velocity.y = -m_speed;
        break;
    case InputAction::eMoveDown:
        m_velocity.y = m_speed;
        break;
    case InputAction::eMoveLeft:
        m_velocity.x = -m_speed;
        m_facingLeft = true;
        break;
    case InputAction::eMoveRight:
        m_velocity.x = m_speed;
        m_facingLeft = false;
        break;
    case InputAction::eLeftMouseClick:
    case InputAction::eNone:
    case InputAction::ePause:
    case InputAction::eRightMouseClick:
    default:
        m_velocity = GraphicsManager::Vec2{ 0.f, 0.f };
        break;
    }
}

CollisionsData Player::getHitbox(float x, float y) const
{
    constexpr float offsetX = 48.f;
    constexpr float offsetY = 24.f;
    constexpr float width = 32.f;
    constexpr float height = 36.f;
    return CollisionsData(x + offsetX, y + offsetY, width, height);
}

bool Player::isBlocked(float x, float y) const
{
    if (!m_walls)
        return false;

    CollisionsData hitbox = getHitbox(x, y);
    for (const auto& wall : *m_walls)
    {
        if (hitbox.intersection(wall))
            return true;
    }
    return false;
}

void Player::update(float dtSeconds)
{
    if (m_attacking)
    {
        m_attackTimer -= dtSeconds;
        if (m_attackTimer <= 0.f)
            m_attacking = false;
    }

    m_hitWall = false;

    float newX = m_position.x + m_velocity.x * dtSeconds;
    if (!isBlocked(newX, m_position.y))
    {
        m_position.x = newX;
    }
    else
    {
        m_hitWall = true;
    }

    float newY = m_position.y + m_velocity.y * dtSeconds;
    if (!isBlocked(m_position.x, newY))
    {
        m_position.y = newY;
    }
    else
    {
        m_hitWall = true;
    }
    auto& gm = GraphicsManager::GetInstance();

    std::string desiredAnimation = "idle";
    if (m_attacking)
    {
        desiredAnimation = m_facingLeft ? "attackLeft" : "attack";
    }
    else if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        desiredAnimation = "walk";
    }

    if (desiredAnimation != m_currentAnimation)
    {
        m_currentAnimation = desiredAnimation;
        gm.setAnimation(m_spriteId, desiredAnimation);
    }

    gm.setFlipped(m_spriteId, m_facingLeft && !m_attacking);
    gm.setPosition(m_spriteId, m_position);
}