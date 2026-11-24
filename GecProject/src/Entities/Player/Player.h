#pragma once

#include "../src/InputManager/InputListener/IReceiveInput.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include "../Entity.h"
#include <string>
#include <vector>

// Player entity. Can be controlled by the player and has a sprite and hitbox.
// The player can move around and collide with walls and other entities.

class Player : public Entity, public IReceiveInput
{
public:
    Player();
    ~Player();

    void handleInput(InputAction action) override;

    void update(float dtSeconds, const std::vector<CollisionsData>& blockingHitboxes);

private:
    float m_speed = 100.f;

    bool m_mouseHeld = false;

    std::string m_currentAnimation = "idle";
};