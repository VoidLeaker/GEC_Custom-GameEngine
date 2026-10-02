/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "ExternalHeaders.h"
#include "RedirectCout.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void DefineGUI(sf::CircleShape& shape, float& circleRadius, sf::Sound& mySound);
float myShape(0.5f);
float circleRadius(10.f);

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

    // Create a simple shape to draw
    sf::CircleShape shape(circleRadius);
    shape.setFillColor(sf::Color::Blue);

    // Clock required by ImGui
    sf::Clock uiDeltaClock;

    sf::Texture myTexture;
    if (!myTexture.loadFromFile("biggboss.png"))
        return 1;

    sf::Sprite* mySprite = new sf::Sprite(myTexture);

    sf::SoundBuffer s;
    s.loadFromFile("shrek-oh-hello-there.mp3");

    sf::Sound mySound(s);

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

        // The UI gets defined each time
        DefineGUI(shape, circleRadius, mySound);

        // Clear the window
        window.clear();

        // Draw the shape
        window.draw(*mySprite);
        window.draw(shape);

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
void DefineGUI(sf::CircleShape& shape, float& circleRadius, sf::Sound& mySound)
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("GEC");				// Create a window called "3GP" and append into it.

    ImGui::Text("BOOMSTICK IS THE BEST WEAPON!");	      	// Display some text (you can use a format strings too)	

    ImGui::Button("GO BUY BOOMSTICK NOW");			// Buttons return true when clicked (most widgets return true when edited/activated)

    if (ImGui::Button("Blue"))
    {
        shape.setFillColor(sf::Color::Blue);
    }
    if (ImGui::Button("Red"))
    {
        shape.setFillColor(sf::Color::Red);
    }
    if (ImGui::Button("Green"))
    {
        shape.setFillColor(sf::Color::Green);
    }

    if (ImGui::Button("Play Shrek Sound"))
    {
        mySound.play();
    }
    if (ImGui::Button("Play Sound"))
    {

    }


    if (ImGui::SliderFloat("Move Slider", &circleRadius, 0.0f, 100.f))
    {
        shape.setRadius({ circleRadius });
    }

    //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable
    // //  ImGui::Checkbox("Cull Face", &m_cullFace);
    // // ImGui::SliderFloat("Speed", &gAnimationSpeed, 0.01f, 0.3f);	// Slider from 0.0 to 1.0

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
}
