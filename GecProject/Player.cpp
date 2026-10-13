#include "Player.h"
#include "src/InputManager/InputManager.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Player::Player()
    : m_sprite("Assets/Textures/MaleZombie/idle_combined.png", 631, 521)
{
    INPUT_MAN.addListener(this);

    m_sprite.addAnimation("attack", "Assets/Textures/MaleZombie/attack_combined.png", 631, 521);
    m_sprite.addAnimation("walk", "Assets/Textures/MaleZombie/walk_combined.png", 631, 521);

    m_sprite.setPosition(m_position);
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
    case InputAction::eNone:
    case InputAction::ePause:
    default:
        m_velocity = sf::Vector2f(0.f, 0.f);
        break;
    }
}

void Player::update(sf::Time dt)
{
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        movement.y -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        movement.y += m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        movement.x -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        movement.x += m_speed;

    m_velocity = movement;

    bool attacking = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (attacking)
        setCurrentAnimation("attack");
    else if (m_velocity.x != 0.f || m_velocity.y != 0.f)
        setCurrentAnimation("walk");
    else
        setCurrentAnimation("default");

    m_position += m_velocity * dt.asSeconds();
    m_sprite.setPosition(m_position);

    m_sprite.update(dt);
}

void Player::draw(sf::RenderWindow& window)
{
    m_sprite.draw(&window);
}

void Player::setCurrentAnimation(const std::string& name)
{
    m_sprite.setCurrentAnimation(name);
}

void Player::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;
    m_sprite.setPosition(pos);
}

sf::Vector2f Player::getPosition() const
{
    return m_position;
}