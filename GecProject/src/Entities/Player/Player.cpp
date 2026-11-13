#include "Player.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/SpritesRelated/AnimatedSetData.h"

Player::Player()
    : Entity(0, CollisionsData(48.f, 24.f, 32.f, 36.f))
{
    m_position.position = GraphicsManager::Vec2{ 100.f, 100.f };
    INPUT_MAN.addListener(this);

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

    createSprite("idle");
    gm.setAnimation(m_sprite.spriteId, "idle");
}

Player::~Player()
{
    INPUT_MAN.removeListener(this);
}

void Player::handleInput(InputAction action)
{
    switch (action)
    {
    case InputAction::eMoveUp:
        m_velocity.velocity.y = -m_speed;
        break;
    case InputAction::eMoveDown:
        m_velocity.velocity.y = m_speed;
        break;
    case InputAction::eMoveLeft:
        m_velocity.velocity.x = -m_speed;
        m_sprite.facingLeft = true;
        break;
    case InputAction::eMoveRight:
        m_velocity.velocity.x = m_speed;
        m_sprite.facingLeft = false;
        break;
    case InputAction::eLeftMouseClick:
    case InputAction::eNone:
    case InputAction::ePause:
    case InputAction::eRightMouseClick:
    default:
        m_velocity.velocity = GraphicsManager::Vec2{ 0.f, 0.f };
        break;
    }
}

void Player::update(float dtSeconds, const std::vector<CollisionsData>& blockingHitboxes)
{
    moveWithCollisions(dtSeconds, blockingHitboxes);
    auto& gm = GraphicsManager::GetInstance();

    std::string desiredAnimation = "idle";

    if (m_velocity.velocity.x != 0.f || m_velocity.velocity.y != 0.f)
    {
        desiredAnimation = "walk";
    }

    if (desiredAnimation != m_currentAnimation)
    {
        m_currentAnimation = desiredAnimation;
        gm.setAnimation(m_sprite.spriteId, desiredAnimation);
    }

    syncSprite();
}