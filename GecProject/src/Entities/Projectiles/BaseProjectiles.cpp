#include "BaseProjectiles.h"

BaseProjectiles::BaseProjectiles(const std::string& animation, const CollisionsData& hitbox)
	: Entity(0, hitbox)
{
	createSprite(animation);
}
