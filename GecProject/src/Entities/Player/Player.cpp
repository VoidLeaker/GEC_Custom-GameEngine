#include "Player.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/AnimatedSetData.h"

Player::Player()
{
    INPUT_MAN.addListener(this);

    auto& gm = GraphicsManager::GetInstance();

    gm.loadTexture("zombie_idle", "Assets/Textures/MaleZombie/idle_combined.png");
    gm.loadTexture("zombie_attack", "Assets/Textures/MaleZombie/attack_combined.png");
    gm.loadTexture("zombie_walk", "Assets/Textures/MaleZombie/walk_combined.png");

    AnimatedSetData idleSet;
    idleSet.textureName = "zombie_idle";
    idleSet.numFrames = 9;
    idleSet.frameWidth = 631;
    idleSet.frameHeight = 521;
    idleSet.frameSeconds = 0.12f;
    idleSet.isHorizontal = false;
    idleSet.isLoop = true;

    AnimatedSetData attackSet;
    attackSet.textureName = "zombie_attack";
    attackSet.numFrames = 9;
    attackSet.frameWidth = 631;
    attackSet.frameHeight = 521;
    attackSet.frameSeconds = 0.08f;
    attackSet.isHorizontal = false;
    attackSet.isLoop = false;

    AnimatedSetData walkSet;
    walkSet.textureName = "zombie_walk";
    walkSet.numFrames = 9;
    walkSet.frameWidth = 631;
    walkSet.frameHeight = 521;
    walkSet.frameSeconds = 0.10f;
    walkSet.isHorizontal = false;
    walkSet.isLoop = true;

    gm.addAnimationSet("idle", idleSet);
    gm.addAnimationSet("attack", attackSet);
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
        break;
    case InputAction::eMoveRight:
        m_velocity.x = m_speed;
        break;
    case InputAction::eLeftMouseClick:
        m_attacking = true;
        break;
    case InputAction::eNone:
    case InputAction::ePause:
    case InputAction::eRightMouseClick:
    default:
        m_velocity = GraphicsManager::Vec2{ 0.f, 0.f };
        m_attacking = false;
        break;
    }
}

void Player::update(float dtSeconds)
{
    m_position.x += m_velocity.x * dtSeconds;
    m_position.y += m_velocity.y * dtSeconds;

    auto& gm = GraphicsManager::GetInstance();

    std::string desiredAnimation = "idle";
    if (m_attacking)
    {
        desiredAnimation = "attack";
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

    gm.setPosition(m_spriteId, m_position);
}