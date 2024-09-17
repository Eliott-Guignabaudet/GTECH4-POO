#include "Fighter.h"

#pragma region Getteur / Setteur

void Fighter::SetDirection(Maths::Vector2& dir)
{
	m_dir = dir;
}

Maths::Vector2& Fighter::GetDirection()
{
	return m_dir;
}

void Fighter::SetMaxLife(int maxLife)
{
	m_maxLife = maxLife;
}

int Fighter::GetMaxLife()
{
	return m_maxLife;
}

void Fighter::SetAttackDamage(int attackDamage)
{
	m_attackDamage = attackDamage;
}

int Fighter::GetAttackDamage()
{
	return m_attackDamage;
}

void Fighter::SetSizeMove(int sizeCanMove)
{
	m_sizeCanMove = sizeCanMove;
}

int Fighter::GetSizeMove()
{
	return m_sizeCanMove;
}

#pragma endregion

#pragma region Class function

Fighter::Fighter() :
	Entity::Entity(),
	m_dir(0, 0),
	m_maxLife(0),
	m_life(0),
	m_attackDamage(0),
	m_sizeCanMove(0)
{

}

Fighter::Fighter(Maths::Vector2* pos, char sprite, int maxLife, int attackDamage, int sizeCanMove) :
	Entity::Entity(pos, sprite),
	m_dir(0, 0),
	m_maxLife(maxLife),
	m_life(maxLife),
	m_attackDamage(attackDamage),
	m_sizeCanMove(sizeCanMove)
{

}

//std::vector<Entity*> Fighter::NearFighter(std::vector<std::vector<Entity*>> tab)
//{
//	std::vector<Entity*> 
//	return nullptr;
//}

void Fighter::Attack(Fighter* target)
{
	target->TakeDamage(GetAttackDamage());
}

void Fighter::TakeDamage(int damage)
{
	m_life -= damage;
}

void Fighter::Die()
{

}

#pragma endregion
