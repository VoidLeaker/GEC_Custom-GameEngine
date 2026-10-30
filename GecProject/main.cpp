/*
    GecProject - For GEC students to use as a start point for their projects.
    Already has SFML linked and ImGui set up.
*/

#include "../src/Misc/ExternalHeaders.h"
#include "../src/Misc/RedirectCout.h"
#include <iostream>
#include "src/Game/Game.h"

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

    Game game;
    game.run();

    std::cout << "Finished!" << std::endl;

    return 0;
}
