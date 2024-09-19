#include "Fighter.h"

std::function<void(Fighter*)> Fighter::OnRedrawMoveFighter;

#pragma region Getteur / Setteur

void Fighter::SetDirection(Vector2& dir)
{
	m_dir = dir;
}

Vector2& Fighter::GetDirection()
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
	m_sizeCanMove(0),
	isHisTurn(false)
{

}

Fighter::Fighter(Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove) :
	Entity::Entity(pos, sprite),
	m_dir(0, 0),
	m_maxLife(maxLife),
	m_life(maxLife),
	m_attackDamage(attackDamage),
	m_sizeCanMove(sizeCanMove),
	isHisTurn(false)
{
	m_listPosPossibilities = std::vector<Vector2>();
}

void Fighter::SetMovePosPossibility(int xLimit, int Ylimit)
{
	int nb = 1;
	for (int i = 1; i <= m_sizeCanMove; i++) 
	{
		nb = nb + (i * 4);
	}

	m_listPosPossibilities.clear();

	for (int i = m_pos.m_x - m_sizeCanMove; i <= m_pos.m_x + m_sizeCanMove; i++)
	{
		if (i < 0 || i >= xLimit) {
			continue;
		}

		for (int j = m_pos.m_y - m_sizeCanMove; j <= m_pos.m_y + m_sizeCanMove; j++)
		{
			if (j < 0 || j >= Ylimit) {
				continue;
			}

			int offsetX = abs(m_pos.m_x - i);
			int offsetY = abs(m_pos.m_y - j);

			if (offsetX + offsetY <= m_sizeCanMove) 
			{
				m_listPosPossibilities.push_back(Vector2(i, j));
			}
			
		}
	}
}

std::vector<Vector2> Fighter::GetMovePosPossibility()
{
	return m_listPosPossibilities;
}

void Fighter::SetRemoveFighterPosPossibility(std::vector<Fighter*>* fighters)
{
	for (int i = 0; i < m_listPosPossibilities.size();)
	{
		bool positionOccupied = false;

		for (Entity* otherFighter : *fighters)
		{
			if (otherFighter->GetPosition() == m_listPosPossibilities[i] && GetPosition() != m_listPosPossibilities[i])
			{
				positionOccupied = true;
				break;
			}
		}

		if (positionOccupied)
		{
			m_listPosPossibilities.erase(m_listPosPossibilities.begin() + i);
		}
		else
		{
			++i;
		}
	}
}


void Fighter::Move()
{
	OnRedrawMovePossibilities();
}

void Fighter::OnRedrawMovePossibilities()
{
	if (OnRedrawMoveFighter)
	{
		OnRedrawMoveFighter(this);
	}
}

void Fighter::Attack(Fighter* target)
{
	target->TakeDamage(GetAttackDamage(), this);
}

void Fighter::TakeDamage(int damage, Fighter* target)
{
	m_life -= damage;
}

void Fighter::Die()
{

}

#pragma endregion
