#include "Spectre.h"
#include "Hero.h"

Spectre::Spectre() :
	Mob::Mob()
{
	m_name = "Spectre";
}

Spectre::Spectre(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'S', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Faible
	m_name = "Spectre";
}

Vector2 Spectre::GetNewPosition(int sizeCanMove)
{
	if (sizeCanMove == 0) 
	{
		sizeCanMove = GetSizeMove();
	}
	Vector2 posSpectre = GetPosition();
	int maxDist = 0;

	for (Vector2 pos : GetMovePosPossibility())
	{
		int dist = Vector2::GetDistance(pos, GetHeroTarget()->GetPosition());
		if (maxDist < dist && Vector2::GetDistance(GetPosition(), pos) == sizeCanMove)
		{
			posSpectre = pos;
			maxDist = dist;
		}
	}

	return posSpectre;
}

void Spectre::ExecuteCapacity()
{
	//Fuit dans la direction opposée pour éviter le héros
	Move();
	SendMessage("Utilise sa capacité");

}

void Spectre::GetKillRewards()
{
	GetHeroTarget()->HealPlayer();
}
