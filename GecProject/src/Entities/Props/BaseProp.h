#pragma once
#include "../Entity.h"

// BaseProp entity. Can be interacted with by the player and has a sprite and hitbox.
class BaseProp : public Entity
{
public:
	BaseProp(EntityId id, const CollisionsData& hitbox);
	~BaseProp() override = default;
};