#pragma once

#include <SFML/Graphics.hpp>

#include "../../GameData/CollisionsData.h"

class CollisionDebug
{
public:
	explicit CollisionDebug(sf::Keyboard::Key toggleKey = sf::Keyboard::Key::F1)
		: m_toggleKey(toggleKey) {}

	bool isEnabled() const { return m_enabled; }

	void handleEvent(const sf::Event& event)
	{
		if (const auto* pressed = event.getIf<sf::Event::KeyPressed>())
		{
			if (pressed->code == m_toggleKey && !m_keyHeld)
			{
				m_enabled = !m_enabled;
				m_keyHeld = true;
			}
		}
		else if (const auto* released = event.getIf<sf::Event::KeyReleased>())
		{
			if (released->code == m_toggleKey)
				m_keyHeld = false;
		}
		else if (event.is<sf::Event::FocusLost>())
		{
			m_keyHeld = false;
		}
	}

	void draw(sf::RenderTarget& target, const CollisionsData& hitbox, sf::Color color) const
	{
		if (!m_enabled)
			return;

		sf::RectangleShape shape({ hitbox.m_width, hitbox.m_height });
		shape.setPosition({ hitbox.m_posX, hitbox.m_posY });
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(color);
		shape.setOutlineThickness(-1.f);
		target.draw(shape);
	}

private:
	sf::Keyboard::Key m_toggleKey;
	bool m_enabled = false;
	bool m_keyHeld = false;
};

