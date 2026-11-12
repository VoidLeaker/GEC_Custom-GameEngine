#include "BaseProjectiles.h"

BaseProjectiles::BaseProjectiles(const std::string& animation, const CollisionsData& hitbox)
	: m_hitbox(hitbox)
{
	auto& gm = GraphicsManager::GetInstance();
	m_spriteId = gm.createSprite(animation);
	gm.setPosition(m_spriteId, m_position);
}

BaseProjectiles::~BaseProjectiles()
{
	if (m_spriteId != 0)
		GraphicsManager::GetInstance().destroySprite(m_spriteId);
}

void BaseProjectiles::setPosition(const GraphicsManager::Vec2& pos)
{
	m_position = pos;
	GraphicsManager::GetInstance().setPosition(m_spriteId, m_position);
}

CollisionsData BaseProjectiles::getCurrentHitbox() const
{
	return CollisionsData(m_position.x + m_hitbox.m_posX, m_position.y + m_hitbox.m_posY, m_hitbox.m_width, m_hitbox.m_height, m_hitbox.m_shape);
}

void BaseProjectiles::setFlipped(bool flipped)
{
	GraphicsManager::GetInstance().setFlipped(m_spriteId, flipped);
}
