#include "InputManager.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

void InputManager::addListener(IReceiveInput* listener)
{
    if (listener)
        m_listeners.push_back(listener);
}

void InputManager::removeListener(IReceiveInput* listener)
{
    m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
}

void InputManager::Update()
{
    InputAction action = InputAction::eNone;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        action = InputAction::eMoveUp;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        action = InputAction::eMoveDown;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        action = InputAction::eMoveLeft;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        action = InputAction::eMoveRight;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        action = InputAction::ePause;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        action = InputAction::eLeftMouseClick;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        action = InputAction::eRightMouseClick;
    }
    else
    {
        action = InputAction::eNone;
    }

    for (IReceiveInput* listener : m_listeners)
    {
        if (listener)
            listener->handleInput(action);
    }
}