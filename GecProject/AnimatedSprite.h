#pragma once
#include "SFML/Graphics.hpp"

class AnimatedSprite
{
public:

	AnimatedSprite(std::string fileLocation, int width, int height);

	void update(sf::Time dt);

	void draw(sf::RenderWindow* window);

private:
	void nextFrame();

	sf::Sprite* m_sprite = nullptr;

	sf::Texture m_loadedTexture = sf::Texture();

	int m_currentFrame = 0;
	int m_maxFrame = 0;

	int m_width = 0;
	int m_height = 0;

	sf::Time m_timer{ sf::Time::Zero };

};

