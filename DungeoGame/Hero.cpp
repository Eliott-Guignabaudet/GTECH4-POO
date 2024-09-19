#include "Hero.h"

Hero::Hero() :
	Fighter::Fighter()
{

}

Hero::Hero(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove) :
	Fighter::Fighter(pos, '@', maxLife, attackDamage, sizeCanMove)
{
	isHisTurn = true;
}

void Hero::Move()
{
	Vector2 dir = GetDirection();
	int newX = m_pos.m_x + dir.m_x;
	int newY = m_pos.m_y + dir.m_y;

	for (Vector2 posPossible : GetMovePosPossibility())
	{
		if (newX == posPossible.m_x && newY == posPossible.m_y)
		{
			m_pos.m_x = newX;
			m_pos.m_y = newY;
			OnRedrawMovePossibilities();
			return;
		}
	}
}

void Hero::SetNearPosPlayer(std::vector<Fighter*>* fighters)
{
	nearPos = std::vector<Entity*>();

	for (int i = m_pos.m_x - 1; i <= m_pos.m_x + 1; i++)
	{
		for (int j = m_pos.m_y - 1; j <= m_pos.m_y + 1; j++)
		{
			int offsetX = abs(m_pos.m_x - i);
			int offsetY = abs(m_pos.m_y - j);

			if (offsetX + offsetY == 1)
			{
				nearPos.push_back(new Entity(Vector2(i, j)));
			}

		}
	}

	for (Entity* entity : nearPos) 
	{
		for (Fighter* otherFighter : *fighters)
		{
			if (otherFighter->GetPosition() == entity->GetPosition()) 
			{
				entity = otherFighter;
			}
		}
	}
}

std::vector<Entity*>& Hero::GetNearEntityPlayer()
{
	return nearPos;
}
