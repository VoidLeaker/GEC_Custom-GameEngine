#pragma once
#include "../Entity.h"

// Chest entity. Can be opened by the player and has a sprite and hitbox.
class Chest : public Entity
{
public:
	Chest(EntityId id, const CollisionsData& hitbox);
	~Chest() override = default;
};