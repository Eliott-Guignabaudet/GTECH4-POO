#include "Mob.h"
#include "Hero.h"
#include <Windows.h>

Mob::Mob() :
	Fighter::Fighter(),
	m_targetPlayer(nullptr),
	m_cooldown(0)
{
	m_name = "Mob";

}

Mob::Mob(Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* target) :
	Fighter::Fighter(pos, sprite, maxLife, attackDamage, sizeCanMove),
	m_targetPlayer(target),
	m_cooldown(cooldown)
{
	m_name = "Mob";
}

Vector2 Mob::GoToPlayer(int sizeCanMove)
{
	if (sizeCanMove == 0)
	{
		sizeCanMove = GetSizeMove();
	}

	int minDist = INT_MAX;
	std::vector<Vector2> listPos = std::vector<Vector2>();

	for (Vector2 pos : GetMovePosPossibility())
	{
		int dist = Vector2::GetDistance(pos, m_targetPlayer->GetPosition());
		int distCanMove = Vector2::GetDistance(GetPosition(), pos);

		if (minDist > dist && distCanMove == sizeCanMove)
		{
			minDist = dist;
			listPos.clear();
			listPos.push_back(pos);
		}
		else if (minDist == dist && distCanMove == sizeCanMove)
		{
			listPos.push_back(pos);
		}
	}

	if (!listPos.empty())
	{
		int id = std::rand() % listPos.size();
		return listPos[id];
	}

	return GetPosition();
}

Vector2 Mob::GoNearPlayer(int sizeCanMove)
{
	if (sizeCanMove == 0)
	{
		sizeCanMove = GetSizeMove();
	}

	Vector2 posPlayer = m_targetPlayer->GetPosition();
	int dist = Vector2::GetDistance(GetPosition(), posPlayer);
	std::vector<Vector2> listPos = std::vector<Vector2>();

	if (dist - 1 <= sizeCanMove)
	{
		for (Vector2 posMoved : GetMovePosPossibility())
		{
			if (Vector2::GetDistance(posMoved, posPlayer) == 1)
			{
				listPos.push_back(posMoved);
			}
		}

		if (!listPos.empty())
		{
			int id = std::rand() % listPos.size();
			return listPos[id];
		}
	}

	return GetPosition();
}

void Mob::Move()
{
	OnRedrawMovePossibilities();

	//for (int i = 0; i < GetSizeMove(); i++) 
	//{
	//	Sleep(500);
	//	Vector2 pos = GetPosition();
	//	Vector2 newPos = GetNewPosition(1);

	//	if (pos != newPos)
	//	{
	//		SetPosition(newPos);
	//		OnRedrawMovePossibilities();
	//	}
	//}

	Sleep(500);
	Vector2 pos = GetPosition();
	Vector2 newPos = GetNewPosition();

	if (pos != newPos)
	{
		SetPosition(newPos);
		OnRedrawMovePossibilities();
	}

	Sleep(500);
}

void Mob::SetHeroTarget(Hero* target)
{
	m_targetPlayer = target;
}

Hero* Mob::GetHeroTarget()
{
	return m_targetPlayer;
}

void Mob::SetNearPos(Vector2 pos)
{
	m_nearPoses[0] = { pos.m_x + 1, pos.m_y };
	m_nearPoses[1] = { pos.m_x - 1, pos.m_y };
	m_nearPoses[2] = { pos.m_x, pos.m_y + 1 };
	m_nearPoses[3] = { pos.m_x, pos.m_y - 1 };
}

Vector2* Mob::GetNearPos()
{
	return m_nearPoses;
}

void Mob::SetCapacityTxt(std::string txt)
{
	m_capacityTxt = txt;
}

std::string Mob::GetCapacityTxt()
{
	return m_capacityTxt;
}

void Mob::SetPercentReward(int percent)
{
	m_percentReward = percent;
}

int Mob::GetPercentReward()
{
	return m_percentReward;
}

void Mob::Die()
{
	Fighter::Die();
	GetKillRewards();
}
