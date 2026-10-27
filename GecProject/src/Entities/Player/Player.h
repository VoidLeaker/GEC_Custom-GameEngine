#pragma once

#include "../src/InputManager/IReceiveInput.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include <string>
#include <vector>

class Player : public IReceiveInput
{
public:
    Player();
    ~Player();

    void handleInput(InputAction action) override;

    void update(float dtSeconds);
    void draw() {}

    void setPosition(const GraphicsManager::Vec2& pos);
    GraphicsManager::Vec2 getPosition() const;

    void setWalls(const std::vector<CollisionsData>* walls) { m_walls = walls; }
    CollisionsData getHitbox(float x, float y) const;
    bool isHittingWall() const { return m_hitWall; }
    CollisionsData getCurrentHitbox() const { return getHitbox(m_position.x, m_position.y); }

private:

    bool m_hitWall = false;
    bool isBlocked(float x, float y) const;
    const std::vector<CollisionsData>* m_walls = nullptr;

    GraphicsManager::SpriteId m_spriteId = 0;
    GraphicsManager::Vec2 m_position{ 100.f, 100.f };
    GraphicsManager::Vec2 m_velocity{ 0.f, 0.f };
    
    float m_speed = 100.f;

    bool m_attacking = false;
    bool m_mouseHeld = false;
    float m_attackTimer = 0.f;
    float m_attackDuration = 0.48f;

    bool m_facingLeft = false;
    std::string m_currentAnimation = "idle";
};