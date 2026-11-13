#pragma once
#include "../src/Graphics/GraphicsManager.h"
#include "../src/GameData/CollisionsData.h"
#include "../Entity.h"
#include <string>

class BaseProjectiles : public Entity
{
public:
	BaseProjectiles(const std::string& animation, const CollisionsData& hitbox);
	~BaseProjectiles() override = default;
};

