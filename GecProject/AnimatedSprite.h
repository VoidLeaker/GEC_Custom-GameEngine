#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>

class AnimatedSprite
{
public:
	AnimatedSprite(std::string fileLocation, int width, int height);

	void update(sf::Time dt);

	void draw(sf::RenderWindow* window);

	void addAnimation(std::string name, std::string fileLocation, int width, int height);

	void setCurrentAnimation(std::string animationName);

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;

private:
	void nextFrame();

	sf::Sprite* m_sprite = nullptr;
	std::map<std::string, sf::Texture*> m_textures;
	std::string m_currentAnimationName = "";

	int m_currentFrame = 0;
	int m_maxFrame = 0;

	int m_width = 0;
	int m_height = 0;

	bool m_horizontal = false;

	sf::Time m_timer{ sf::Time::Zero };
};