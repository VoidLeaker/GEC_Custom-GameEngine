#include "Game.h"

#include "../Misc/ExternalHeaders.h"

namespace
{
	void DefineGUI(int fps, bool hitWall)
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("GEC");
		ImGui::Text("Milestone 2 Testing");
		ImGui::Separator();
		ImGui::Text("Stable FramePerSecond: %d", fps);

		if (hitWall)
		{
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Wall hit: YES");
		}
		else
		{
			ImGui::TextColored(ImVec4(0.3f, 1.f, 0.3f, 1.f), "Wall hit: NO");
		}

		ImGui::End();
	}
}

void Game::run()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Start Project");

	if (!ImGui::SFML::Init(window))
	{
		return;
	}

	sf::Clock uiDeltaClock;
	sf::Clock updateClock;

	int fpsCounter = 0;
	int lastKnownFps = 0;
	sf::Clock fpsClock;

	Player player;
	Enemy enemyA;
	Enemy enemyB;
	enemyA.setPosition({ 300.f, 300.f });
	enemyB.setPosition({ 500.f, 120.f });

	sf::Texture backgroundTexture;
	std::unique_ptr<sf::Sprite> backgroundSprite;
	const bool hasBackground = backgroundTexture.loadFromFile("Assets/Textures/Misc/PH_grass.png");
	if (hasBackground)
	{
		backgroundSprite = std::make_unique<sf::Sprite>(backgroundTexture);

		const sf::Vector2u textureSize = backgroundTexture.getSize();
		if (textureSize.x > 0 && textureSize.y > 0)
		{
			const sf::Vector2u windowSize = window.getSize();
			backgroundSprite->setScale(
				sf::Vector2f{
					static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
					static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y)
				});
		}
	}

	std::vector<CollisionsData> walls;
	walls.emplace_back(300.f, 200.f, 40.f, 200.f);
	player.setWalls(&walls);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, event.value());

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		ImGui::SFML::Update(window, uiDeltaClock.restart());

		if (fpsClock.getElapsedTime().asSeconds() >= 1)
		{
			lastKnownFps = fpsCounter;
			fpsCounter = 0;
			fpsClock.reset();
		}
		fpsCounter++;

		DefineGUI(lastKnownFps, player.isHittingWall());

		INPUT_MAN.Update();

		sf::Time dt = updateClock.restart();

		player.update(dt.asSeconds());
		enemyA.update(dt.asSeconds(), player.getPosition(), { enemyB.getCurrentHitbox() });
		enemyB.update(dt.asSeconds(), player.getPosition(), { enemyA.getCurrentHitbox() });
		GraphicsManager::GetInstance().update(dt.asSeconds());

		window.clear();
		if (backgroundSprite)
		{
			window.draw(*backgroundSprite);
		}
		player.draw();
		enemyA.draw();
		enemyB.draw();

		GraphicsManager::GetInstance().draw(window);

		for (const auto& wall : walls)
		{
			sf::RectangleShape wallShape({ wall.m_width, wall.m_height });
			wallShape.setPosition({ wall.m_posX, wall.m_posY });
			wallShape.setFillColor(sf::Color(150, 150, 150));
			window.draw(wallShape);
		}

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
