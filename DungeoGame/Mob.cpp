#include "Mob.h"
#include "Hero.h"
#include <Windows.h>

Mob::Mob() :
	Fighter::Fighter(),
	m_targetPlayer(nullptr),
	m_cooldown(0)
{

}

Mob::Mob(Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* target) :
	Fighter::Fighter(pos, sprite, maxLife, attackDamage, sizeCanMove),
	m_targetPlayer(target),
	m_cooldown(cooldown)
{

}

void Mob::Move()
{
	OnRedrawMovePossibilities();
	Sleep(750);
	Vector2 pos = GetPosition();
	Vector2 newPos = GetNewPosition();

	if (pos != newPos)
	{
		SetPosition(newPos);
		OnRedrawMovePossibilities();
	}
	Sleep(750);
}

void Mob::SetHeroTarget(Hero* target)
{
	m_targetPlayer = target;
}

Hero* Mob::GetHeroTarget()
{
	return m_targetPlayer;
}
