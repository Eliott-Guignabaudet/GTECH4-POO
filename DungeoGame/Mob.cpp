#include "Mob.h"

Mob::Mob() :
	m_cooldown(0)
{
	Fighter::Fighter();
}

Mob::Mob(Maths::Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown) :
	m_cooldown(cooldown)
{
	Fighter::Fighter(pos, sprite, maxLife, attackDamage, sizeCanMove);
}

void Mob::SetHeroTarget(Fighter target)
{
	m_targetPlayer = target;
}

void Mob::ExecuteCapacity()
{

}
