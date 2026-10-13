#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string fileLocation, int width, int height)
{
	addAnimation("default", fileLocation, width, height);
	setCurrentAnimation("default");
}

void AnimatedSprite::addAnimation(std::string name, std::string fileLocation, int width, int height)
{
	sf::Texture* newTexture = new sf::Texture();

	if (!newTexture->loadFromFile(fileLocation))
	{
		delete newTexture;
		return;
	}

	m_textures[name] = newTexture;

	m_width = width;
	m_height = height;

	sf::Vector2u texXY = newTexture->getSize();
	m_maxFrame = texXY.y / height;

	if (m_sprite == nullptr)
	{
		m_sprite = new sf::Sprite(*newTexture);
		m_sprite->setTextureRect(sf::IntRect({ 0, m_currentFrame * m_height}, { m_width, m_height }));
	}
}

void AnimatedSprite::setCurrentAnimation(std::string animationName)
{
	if (m_textures.find(animationName) == m_textures.end())
	{
		return;
	}

	m_currentAnimationName = animationName;
	m_sprite->setTexture(*m_textures[animationName]);

	m_currentFrame = 0;
	m_timer = sf::Time::Zero;

	sf::Vector2u texXY = m_textures[animationName]->getSize();
	m_maxFrame = texXY.y / m_height;

	if (m_sprite)
	{
		m_sprite->setTextureRect(sf::IntRect({ 0, m_currentFrame * m_height }, { m_width, m_height }));
	}

}

void AnimatedSprite::update(sf::Time dt)
{
	m_timer += dt;

	sf::Time animationSpeed = sf::seconds(0.1f);

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

	m_sprite->setTextureRect(sf::IntRect({ 0, m_currentFrame * m_height }, { m_width, m_height }));
}

void AnimatedSprite::setPosition(const sf::Vector2f& pos)
{
	if (m_sprite)
		m_sprite->setPosition(pos);
}

sf::Vector2f AnimatedSprite::getPosition() const
{
	if (m_sprite)
		return m_sprite->getPosition();
	return sf::Vector2f{ 0.f, 0.f };
}