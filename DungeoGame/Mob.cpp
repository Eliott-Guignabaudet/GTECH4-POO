#include "Mob.h"

Mob::Mob() :
	Fighter(),
	m_targetPlayer(nullptr),
	m_cooldown(0)
{

}

Mob::Mob(Maths::Vector2* pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Entity* target) :
	Fighter(pos, sprite, maxLife, attackDamage, sizeCanMove),
	m_targetPlayer(target),
	m_cooldown(cooldown)
{

}

void Mob::SetHeroTarget(Entity* target)
{
	m_targetPlayer = target;
}

void Mob::ExecuteCapacity()
{

}
