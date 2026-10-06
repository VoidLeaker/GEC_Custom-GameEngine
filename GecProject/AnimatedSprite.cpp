#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string fileLocation, int width, int height)
{
	if (!m_loadedTexture.loadFromFile(fileLocation))
	{
		// Handle error loading texture
	}
	else 
	{
		m_width = width;
		m_height = height;

		sf::Vector2u texXY = m_loadedTexture.getSize();
		m_maxFrame = texXY.y / height;

		m_sprite = new sf::Sprite(m_loadedTexture);
		m_sprite->setTextureRect(sf::IntRect({0, m_currentFrame * m_height}, { m_width, m_height }));
	}
}

void AnimatedSprite::update(sf::Time dt)
{
	m_timer += dt;

	sf::Time animationSpeed = sf::seconds(0.05f);

	if (m_timer >= animationSpeed)
	{
		m_timer -= animationSpeed;
		nextFrame();
	}

}

void AnimatedSprite::draw(sf::RenderWindow* window)
{
	window->draw(*m_sprite);
}

void AnimatedSprite::nextFrame()
{
	m_currentFrame++;
	if (m_currentFrame >= m_maxFrame)
	{
		m_currentFrame = 0;
	}

	m_sprite->setTextureRect(sf::IntRect({0, m_currentFrame * m_height}, { m_width, m_height }));
}
