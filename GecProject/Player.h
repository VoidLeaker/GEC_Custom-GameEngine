#pragma once

#include "src/InputManager/InputManager.h"
#include "AnimatedSprite.h"
#include "SFML/Graphics.hpp"
#include <string>

class Player : public IReceiveInput
{
public:
    Player();
    ~Player();

    void handleInput(InputAction action) override;

    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void setCurrentAnimation(const std::string& name);

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;

private:
    AnimatedSprite m_sprite;

    sf::Vector2f m_position{ 100.f, 100.f };
    sf::Vector2f m_velocity{ 0.f, 0.f };
    float m_speed = 200.f;
};