#include "Hero.h"

Hero::Hero() :
	Fighter::Fighter()
{
	m_name = "Hero";
}

Hero::Hero(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove) :
	Fighter::Fighter(pos, '@', maxLife, attackDamage, sizeCanMove)
{
	isHisTurn = true;
	m_name = "Hero";
}

void Hero::HealPlayer()
{
	SetMaxLife(GetMaxLife());
}

void Hero::UpgradeAttack(int upgrade)
{
	SetAttackDamage(GetAttackDamage() + upgrade);
}

void Hero::AttackAround()
{
	for (Fighter* fighter : m_nearPos) 
	{
		Attack(fighter);
	}
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

void Hero::SetNearPosPlayer(const std::vector<Fighter*>& fighters)
{
	m_nearPos = std::vector<Fighter*>();
	Vector2 nearPoses[4] = {
		{m_pos.m_x + 1, m_pos.m_y},
		{m_pos.m_x - 1, m_pos.m_y},
		{m_pos.m_x , m_pos.m_y + 1},
		{m_pos.m_x , m_pos.m_y - 1}
	};

	for (Fighter* otherFighter : fighters)
	{
		for (Vector2 nearPose : nearPoses)
		{
			if (otherFighter->GetPosition() == nearPose) 
			{
				m_nearPos.push_back(otherFighter);
			}
		}
	}
}

std::vector<Fighter*>& Hero::GetNearFightPlayer()
{
	return m_nearPos;
}

void Hero::Die()
{
	Fighter::Die();
	//TODO Turn to game over state
}
