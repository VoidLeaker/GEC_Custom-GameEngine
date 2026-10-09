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

private:
	void nextFrame();

	sf::Sprite* m_sprite = nullptr;

	std::map<std::string, sf::Texture*> m_textures;
	std::string m_currentAnimationName = "";

	int m_currentFrame = 0;
	int m_maxFrame = 0;

	int m_width = 0;
	int m_height = 0;

	sf::Time m_timer{ sf::Time::Zero };
};