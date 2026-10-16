/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "../src/Misc/ExternalHeaders.h"
#include "../src/Misc/RedirectCout.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/Entities/Player/Player.h"
#include "src/InputManager/InputManager.h"
#include "src/Graphics/GraphicsManager.h"

void DefineGUI(sf::Sound& mySound, int FPS);

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

    sf::SoundBuffer s;
    sf::Sound mySound(s);
    s.loadFromFile("Assets/Sounds/shrek-oh-hello-there.mp3");

    int fpsCounter = 0;
    int lastKnownFps = 0;
    sf::Clock fpsClock;

    Player player;

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
        DefineGUI(mySound, lastKnownFps);

        INPUT_MAN.Update();

        sf::Time dt = updateClock.restart();

        player.update(dt.asSeconds());

        // Update graphics animations
        GraphicsManager::GetInstance().update(dt.asSeconds());

        // Clear the window
        window.clear();

        player.draw();

        // Draw all sprites managed by GraphicsManager
        GraphicsManager::GetInstance().draw(window);

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
void DefineGUI(sf::Sound& mySound, int FPS)
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("GEC");				// Create a window called "3GP" and append into it.

    ImGui::Text("BOOMSTICK IS THE BEST WEAPON!");	      	// Display some text (you can use a format strings too)	

    ImGui::Button("GO BUY BOOMSTICK NOW");			// Buttons return true when clicked (most widgets return true when edited/activated)

    if (ImGui::Button("Play Shrek Sound"))
    {
        mySound.play();
    }

    ImGui::Separator();

    //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable
    // //  ImGui::Checkbox("Cull Face", &m_cullFace);
    // // ImGui::SliderFloat("Speed", &gAnimationSpeed, 0.01f, 0.3f);	// Slider from 0.0 to 1.0
    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Text("Stable FramePerSecond: %d", FPS);

    ImGui::End();
}