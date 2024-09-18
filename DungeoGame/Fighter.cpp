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

int Fighter::GetLife()
{
	return m_life;
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
	m_listPosPossible = std::vector<Maths::Vector2>();
}

void Fighter::SetMovePosPossibility(int xLimit, int Ylimit)
{
	int nb = 1;
	for (int i = 1; i <= m_sizeCanMove; i++) 
	{
		nb = nb + (i * 4);
	}

	m_listPosPossible.clear();

	for (int i = m_pos->m_x - m_sizeCanMove; i <= m_pos->m_x + m_sizeCanMove; i++)
	{
		if (i <= 0 || i >= xLimit) {
			continue;
		}

		for (int j = m_pos->m_y - m_sizeCanMove; j <= m_pos->m_y + m_sizeCanMove; j++)
		{
			if (j <= 0 || j >= Ylimit) {
				continue;
			}

			int offsetX = abs(m_pos->m_x - i);
			int offsetY = abs(m_pos->m_y - j);

			if (offsetX + offsetY <= m_sizeCanMove) 
			{
				m_listPosPossible.push_back(Maths::Vector2(i, j));
			}
			
		}
	}
}

std::vector<Maths::Vector2> Fighter::GetMovePosPossibility()
{
	return m_listPosPossible;
}

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

void Fighter::UpdateMovePossibility(int width, int height)
{
	SetMovePosPossibility(width, height);
}

#pragma endregion
