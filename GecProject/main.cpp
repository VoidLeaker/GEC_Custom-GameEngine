/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "../src/Misc/ExternalHeaders.h"
#include "../src/Misc/RedirectCout.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Entities/Player/Player.h"
#include "src/InputManager/InputManager.h"
#include "src/Graphics/GraphicsManager.h"

void DefineGUI(int FPS, bool hitWall);

int main()
{
    // Redirect cout to the Visual Studio output pane
    outbuf ob;
    std::streambuf* sb{ std::cout.rdbuf(&ob) };

    // Redirect cerr
    outbuferr oberr;
    std::streambuf* sberr{ std::cerr.rdbuf(&oberr) };

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GEC Start Project");

    // Set up ImGui (the UI library)
    if (!ImGui::SFML::Init(window))
        return -1;

    // Clock required by ImGui
    sf::Clock uiDeltaClock;
    sf::Clock updateClock;
    
    int fpsCounter = 0;
    int lastKnownFps = 0;
    sf::Clock fpsClock;

    Player player;

    // Walls: x, y, width, height
    std::vector<CollisionsData> walls;
    walls.emplace_back(300.f, 200.f, 40.f, 200.f);
    player.setWalls(&walls);

    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Feed ImGui
            ImGui::SFML::ProcessEvent(window, event.value());

            // User clicked on window close X
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // ImGui must be updated each frame
        ImGui::SFML::Update(window, uiDeltaClock.restart());

        if (fpsClock.getElapsedTime().asSeconds() >= 1)
        {
            lastKnownFps = fpsCounter;
            fpsCounter = 0;
            fpsClock.reset();
        }
        fpsCounter++;

        // The UI gets defined each time
        DefineGUI(lastKnownFps, player.isHittingWall());

        INPUT_MAN.Update();

        sf::Time dt = updateClock.restart();

        player.update(dt.asSeconds());

        // Update graphics
        GraphicsManager::GetInstance().update(dt.asSeconds());

        // Clear the window
        window.clear();
        player.draw();

        // Draw all sprites managed by GraphicsManager
        GraphicsManager::GetInstance().draw(window);

        // Debug: draw walls
        for (const auto& w : walls)
        {
            sf::RectangleShape r({ w.m_width, w.m_height });
            r.setPosition({ w.m_posX, w.m_posY });
            r.setFillColor(sf::Color(150, 150, 150));
            window.draw(r);
        }

        // Debug: draw player body hitbox (red = hitting wall, green = free)
        {
            CollisionsData hb = player.getCurrentHitbox();
            sf::Color c = player.isHittingWall() ? sf::Color::Red : sf::Color::Green;
            sf::RectangleShape box({ hb.m_width, hb.m_height });
            box.setPosition({ hb.m_posX, hb.m_posY });
            box.setFillColor(sf::Color::Transparent);
            box.setOutlineColor(c);
            box.setOutlineThickness(1.f);
            window.draw(box);
        }

        // UI needs drawing last
        ImGui::SFML::Render(window);

        window.display();
    }

    std::cout << "Finished!" << std::endl;

    ImGui::SFML::Shutdown();

    return 0;
}

/*
    Use IMGUI for a simple on screen GUI
    See: https://github.com/ocornut/imgui/wiki/
*/
void DefineGUI(int FPS, bool hitWall)
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("GEC");				// Create a window called "3GP" and append into it.

    ImGui::Text("Milestone 2 Testing");	      	// Display some text (you can use a format strings too)	

    //ImGui::Button("GO BUY BOOMSTICK NOW");			// Buttons return true when clicked (most widgets return true when edited/activated)

    ImGui::Separator();

    //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable
    // //  ImGui::Checkbox("Cull Face", &m_cullFace);
    // // ImGui::SliderFloat("Speed", &gAnimationSpeed, 0.01f, 0.3f);	// Slider from 0.0 to 1.0

    ImGui::Text("Stable FramePerSecond: %d", FPS);

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