#include "Entity.h"

Entity::Entity(EntityId id, const CollisionsData& hitbox)
	: m_id(id)
{
	m_hitbox.localHitbox = hitbox;
}

Entity::~Entity()
{
	if (m_sprite.spriteId != 0)
		GraphicsManager::GetInstance().destroySprite(m_sprite.spriteId);
}

void Entity::createSprite(const std::string& animation)
{
	auto& gm = GraphicsManager::GetInstance();
	m_sprite.spriteId = gm.createSprite(animation);
	gm.setPosition(m_sprite.spriteId, m_position.position);
}

void Entity::syncSprite()
{
	if (m_sprite.spriteId == 0)
		return;
	auto& gm = GraphicsManager::GetInstance();
	gm.setFlipped(m_sprite.spriteId, m_sprite.facingLeft);
	gm.setPosition(m_sprite.spriteId, m_position.position);
}

void Entity::setPosition(const GraphicsManager::Vec2& pos)
{
	m_position.position = pos;
	if (m_sprite.spriteId != 0)
		GraphicsManager::GetInstance().setPosition(m_sprite.spriteId, pos);
}

void Entity::setFlipped(bool flipped)
{
	m_sprite.facingLeft = flipped;
	if (m_sprite.spriteId != 0)
		GraphicsManager::GetInstance().setFlipped(m_sprite.spriteId, flipped);
}

CollisionsData Entity::getHitbox(float x, float y) const
{
	const CollisionsData& h = m_hitbox.localHitbox;
	return CollisionsData(x + h.m_posX, y + h.m_posY, h.m_width, h.m_height, h.m_shape);
}

void Entity::moveWithCollisions(float dtSeconds, const std::vector<CollisionsData>& blockingHitboxes)
{
	m_hitWall = false;

	float moveX = m_velocity.velocity.x * dtSeconds;
	if (m_walls)
	{
		const float limitedX = getCurrentHitbox().limitMovement(moveX, true, *m_walls);
		m_hitWall = limitedX != moveX;
		moveX = limitedX;
	}
	moveX = getCurrentHitbox().limitMovement(moveX, true, blockingHitboxes);
	m_position.position.x += moveX;

	float moveY = m_velocity.velocity.y * dtSeconds;
	if (m_walls)
	{
		const float limitedY = getCurrentHitbox().limitMovement(moveY, false, *m_walls);
		m_hitWall = m_hitWall || limitedY != moveY;
		moveY = limitedY;
	}
	moveY = getCurrentHitbox().limitMovement(moveY, false, blockingHitboxes);
	m_position.position.y += moveY;
}
