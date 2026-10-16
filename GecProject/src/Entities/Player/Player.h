#pragma once

#include "../src/InputManager/IReceiveInput.h"
#include "../src/Graphics/GraphicsManager.h"
#include <string>

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

private:
    GraphicsManager::SpriteId m_spriteId = 0;
    GraphicsManager::Vec2 m_position{ 100.f, 100.f };
    GraphicsManager::Vec2 m_velocity{ 0.f, 0.f };
    float m_speed = 200.f;
    bool m_attacking = false;
    std::string m_currentAnimation = "idle";
};