#include "Game.h"

#include "../DebugTools/Collision/CollisionDebug.h"
#include "../GameData/SpritesRelated/AnimatedSetData.h"
#include "../Misc/ExternalHeaders.h"

namespace
{
	bool RegisterEnemyAnimation(const std::string& name, const std::string& filename, int frames, int frameWidth)
	{
		auto& gm = GraphicsManager::GetInstance();
		if (!gm.loadTexture(name, filename))
			return false;

		AnimatedSetData walkSet;
		walkSet.textureName = name;
		walkSet.numFrames = frames;
		walkSet.frameWidth = frameWidth;
		walkSet.frameHeight = 64;
		walkSet.frameSeconds = 0.10f;
		walkSet.isHorizontal = true;
		walkSet.isLoop = true;
		gm.addAnimationSet(name, walkSet);
		return true;
	}

	void DefineGUI(int fps, bool hitWall, bool collisionDebugEnabled)
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("GEC");
		ImGui::Text("Milestone 2 Testing");
		ImGui::Separator();
		ImGui::Text("Stable FramePerSecond: %d", fps);

		if (collisionDebugEnabled && hitWall)
		{
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Wall hit: YES");
		}
		else if (collisionDebugEnabled)
		{
			ImGui::TextColored(ImVec4(0.3f, 1.f, 0.3f, 1.f), "Wall hit: NO");
		}

		ImGui::End();
	}
}

void Game::run()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Vampire Survivor");

	if (!ImGui::SFML::Init(window))
	{
		return;
	}

	sf::Clock uiDeltaClock;
	sf::Clock updateClock;

	int fpsCounter = 0;
	int lastKnownFps = 0;
	sf::Clock fpsClock;

	// Register enemy animations
	if (!RegisterEnemyAnimation("bluegolem_walk", "Assets/Textures/Monster/BlueGolem-Walk.png", 10, 90) ||
		!RegisterEnemyAnimation("bat_walk", "Assets/Textures/Monster/Bat-Run.png", 8, 64) ||
		!RegisterEnemyAnimation("yellow_skeleton_walk", "Assets/Textures/Monster/Yellow_SwordSkeleton_Walk.png", 10, 96) ||
		!RegisterEnemyAnimation("white_skeleton_walk", "Assets/Textures/Monster/White_SwordSkeleton_Walk.png", 10, 96) ||
		!RegisterEnemyAnimation("mushroom_run", "Assets/Textures/Monster/Mushroom-Run.png", 8, 80) ||
		!RegisterEnemyAnimation("orangegolem_walk", "Assets/Textures/Monster/OrangeGolem-Walk.png", 10, 90))
	{
		ImGui::SFML::Shutdown();
		return;
	}

	Player player;

	// Set up enemies with their respective hitboxes (x, y, width, height)
	Enemy golem("bluegolem_walk", { 26.f, 24.f, 36.f, 40.f });
	Enemy bat("bat_walk", { 20.f, 24.f, 24.f, 24.f, CollisionsData::Shape::Circle });
	Enemy yellowSkeleton("yellow_skeleton_walk", { 38.f, 20.f, 20.f, 44.f });
	Enemy whiteSkeleton("white_skeleton_walk", { 38.f, 20.f, 20.f, 44.f });
	Enemy mushroom("mushroom_run", { 22.f, 30.f, 36.f, 36.f });
	Enemy orangeGolem("orangegolem_walk", { 26.f, 24.f, 36.f, 40.f });

	golem.setPosition({ 350.f, 300.f });
	bat.setPosition({ 500.f, 120.f });
	yellowSkeleton.setPosition({ 400.f, 100.f });
	whiteSkeleton.setPosition({ 140.f, 150.f });
	mushroom.setPosition({ 600.f, 400.f });
	orangeGolem.setPosition({ 200.f, 400.f });

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
	const std::vector<Enemy*> enemies{ &golem, &orangeGolem, &mushroom, &bat, &yellowSkeleton, &whiteSkeleton };
	for (auto* enemy : enemies)
	{
		enemy->setWalls(&walls);
	}
	CollisionDebug collisionDebug;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, event.value());
			collisionDebug.handleEvent(event.value());

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

		DefineGUI(lastKnownFps, player.isHittingWall(), collisionDebug.isEnabled());

		INPUT_MAN.Update();

		sf::Time dt = updateClock.restart();

		std::vector<CollisionsData> enemyHitboxes;
		for (const auto* enemy : enemies)
		{
			enemyHitboxes.push_back(enemy->getCurrentHitbox());
		}
		player.update(dt.asSeconds(), enemyHitboxes);

		for (auto* enemy : enemies)
		{
			std::vector<CollisionsData> blockingHitboxes{ player.getCurrentHitbox() };
			for (const auto* other : enemies)
			{
				if (other != enemy)
					blockingHitboxes.push_back(other->getCurrentHitbox());
			}
			enemy->update(dt.asSeconds(), player.getPosition(), blockingHitboxes);
		}
		GraphicsManager::GetInstance().update(dt.asSeconds());

		window.clear();
		if (backgroundSprite)
		{
			window.draw(*backgroundSprite);
		}
		player.draw();
		bat.draw();
		golem.draw();
		mushroom.draw();
		whiteSkeleton.draw();
		yellowSkeleton.draw();

		GraphicsManager::GetInstance().draw(window);

		for (const auto& wall : walls)
		{
			sf::RectangleShape wallShape({ wall.m_width, wall.m_height });
			wallShape.setPosition({ wall.m_posX, wall.m_posY });
			wallShape.setFillColor(sf::Color(150, 150, 150));
			window.draw(wallShape);
		}

		// Draw hitboxes for debugging
		collisionDebug.draw(window, player.getCurrentHitbox(), sf::Color::Green);
		collisionDebug.draw(window, golem.getCurrentHitbox(), sf::Color::Red);
		collisionDebug.draw(window, bat.getCurrentHitbox(), sf::Color::Red);
		collisionDebug.draw(window, yellowSkeleton.getCurrentHitbox(), sf::Color::Red);
		collisionDebug.draw(window, whiteSkeleton.getCurrentHitbox(), sf::Color::Red);
		collisionDebug.draw(window, mushroom.getCurrentHitbox(), sf::Color::Red);
		collisionDebug.draw(window, orangeGolem.getCurrentHitbox(), sf::Color::Red);
		for (const auto& wall : walls)
		{
			collisionDebug.draw(window, wall, sf::Color::Red);
		}

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
