#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../src/Entities/Player/Player.h"
#include "../src/Entities/Enemy/Enemy.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"

class Game
{
public:
    Game() = default;
    ~Game() = default;

    void run();
};