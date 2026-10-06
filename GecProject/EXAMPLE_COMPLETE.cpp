// ============================================================================
// COMPLETE WORKING EXAMPLE
// ============================================================================
//
// This file shows a complete, ready-to-run example of how to use FpsCounter
// with your existing SFML + ImGui setup.
//
// If you're unsure how to integrate FpsCounter into your project,
// this shows the exact pattern to follow.
//
// ============================================================================

/*

ASSUMING YOU HAVE:
- SFML installed and linked
- ImGui installed with imgui-SFML integration
- Visual Studio project set up

MINIMAL WORKING EXAMPLE:
========================

*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui-SFML.h"
#include "FpsCounter.h"

// Simple GUI function - shows FPS
void DisplayPerformanceUI(FpsCounter& fpsCounter)
{
	// Position window at top-left
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

	ImGui::Begin("Performance Stats", nullptr);

	// Get current FPS
	float fps = fpsCounter.getFps();
	float frameTimeMs = fpsCounter.getFrameTimeMs();
	unsigned long frames = fpsCounter.getFrameCount();

	// Display basic info
	ImGui::Text("FPS: %.1f", fps);
	ImGui::Text("Frame Time: %.2f ms", frameTimeMs);
	ImGui::Text("Total Frames: %lu", frames);

	ImGui::Separator();

	// Color-coded performance indicator
	ImGui::Text("Performance:");
	ImGui::SameLine();

	if (fps >= 55.0f)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 1), "GOOD");
	}
	else if (fps >= 30.0f)
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "ACCEPTABLE");
	}
	else
	{
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "LOW");
	}

	// Show frame time in bar graph
	ImGui::Text("Frame Time Bar: (max 33.3ms for 30fps)");
	float frameTimeRatio = frameTimeMs / 33.3f;
	ImGui::ProgressBar(frameTimeRatio);

	ImGui::End();
}

// ============================================================================
// MAIN FUNCTION - Complete Example
// ============================================================================

int main()
{
	// ========================================
	// Step 1: Create SFML Window
	// ========================================
	sf::RenderWindow window(
		sf::VideoMode({1280u, 720u}),
		"FPS Counter Example - SFML 3.1.0 + ImGui"
	);

	// Optional: cap frame rate for consistent testing
	// window.setFramerateLimit(60);

	// ========================================
	// Step 2: Initialize ImGui
	// ========================================
	if (!ImGui::SFML::Init(window))
	{
		return -1;
	}

	// ========================================
	// Step 3: Create Clock and FPS Counter
	// ========================================
	sf::Clock mainClock;         // Measures time between frames
	FpsCounter fpsCounter(60);   // Averaging 60 frames for smooth display

	// ========================================
	// Step 4: Main Application Loop
	// ========================================
	while (window.isOpen())
	{
		// -------- TIMING --------
		// Get time elapsed since last frame
		auto deltaTime = mainClock.restart();

		// -------- INPUT --------
		// Handle all window events
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			// Pass events to ImGui
			ImGui::SFML::ProcessEvent(window, *event);

			// Close window on X click
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			// Close window on Escape key
			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyEvent->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}
		}

		// -------- UPDATE IMGUI --------
		ImGui::SFML::Update(window, deltaTime);

		// -------- UPDATE FPS COUNTER (IMPORTANT!) --------
		// This MUST be called every frame with delta time in seconds
		fpsCounter.update(deltaTime.asSeconds());

		// -------- UPDATE GAME LOGIC --------
		// (Example: move objects using deltaTime)
		// position += velocity * deltaTime.asSeconds();
		// sprite.update(deltaTime);

		// -------- RENDER --------
		// Clear window with dark background
		window.clear(sf::Color::Black);

		// Render game objects
		// (Example: window.draw(sprite);)

		// -------- RENDER UI --------
		// Display the FPS counter and performance stats
		DisplayPerformanceUI(fpsCounter);

		// Render ImGui
		ImGui::SFML::Render(window);

		// -------- DISPLAY --------
		// Show the frame to the user
		window.display();
	}

	// ========================================
	// Cleanup
	// ========================================
	ImGui::SFML::Shutdown();

	return 0;
}


// ============================================================================
// HOW TO BUILD AND RUN
// ============================================================================
//
// 1. Copy FpsCounter.h and FpsCounter.cpp to your project folder
//
// 2. In Visual Studio:
//    - Right-click Project
//    - Select "Add > Existing Item"
//    - Add FpsCounter.cpp and FpsCounter.h
//
// 3. Replace main.cpp content with the code above
//
// 4. Build (Ctrl+B)
//
// 5. Run (F5)
//
// You should see:
// - Black window
// - FPS counter at top-left
// - Green "GOOD" after 1 second
// - Smooth FPS value that doesn't jump around
//
// ============================================================================


/*

NEXT STEPS - INTEGRATE INTO YOUR PROJECT:
===========================================

Your project already has:
- main.cpp with SFML window
- DefineGUI() function for UI
- AnimatedSprite class

To add FPS counter to your existing code:

1. Add to main.cpp includes:
   #include "FpsCounter.h"

2. In main(), after other clock declarations:
   FpsCounter fpsCounter(60);

3. In the main loop, change:
   ImGui::SFML::Update(window, uiDeltaClock.restart());

   To:
   auto deltaTime = uiDeltaClock.restart();
   ImGui::SFML::Update(window, deltaTime);
   fpsCounter.update(deltaTime.asSeconds());

4. In DefineGUI(), add:
   ImGui::Begin("Performance");
   ImGui::Text("FPS: %.1f", fpsCounter.getFps());
   ImGui::Text("Frame Time: %.2f ms", fpsCounter.getFrameTimeMs());
   ImGui::End();

5. Update DefineGUI() signature:
   void DefineGUI(sf::CircleShape& shape, float& circleRadius, 
				  sf::Sound& mySound, FpsCounter& fpsCounter);

6. Pass fpsCounter when calling:
   DefineGUI(shape, circleRadius, mySound, fpsCounter);

*/
