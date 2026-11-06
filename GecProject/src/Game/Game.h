#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entities/Player/Player.h"
#include "../Entities/Enemy/Enemy.h"
#include "../InputManager/InputManager.h"
#include "../Graphics/GraphicsManager.h"
#include "../GameData/CollisionsData.h"

class Game
{
public:
    Game() = default;
    ~Game() = default;

    void run();
};