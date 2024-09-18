#include "Mower.h"
#include "Hero.h"

Mower::Mower() :
	Mob::Mob()
{

}

Mower::Mower(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'F', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Très puissante
}

void Mower::Move()
{
	Maths::Vector2* pos = GetPosition();
	Maths::Vector2 newPos = GetNewPosition();

	if (*pos != newPos)
	{
		*pos = newPos;
		OnMove();
	}
}


Maths::Vector2 Mower::GetNewPosition()
{
	Maths::Vector2 newPos = Maths::Vector2(0, 0);
	int maxDist = INT_MAX;

	for (Maths::Vector2 pos : GetMovePosPossibility())
	{
		int dist = Maths::Vector2::GetDistance(pos, *GetHeroTarget()->GetPosition());
		if (maxDist > dist)
		{
			newPos = pos;
			maxDist = dist;
		}
	}

	return newPos;
}

void Mower::ExecuteCapacity()
{
	//Capacité spéciale : Se déplace vers le héros, cherchant à se rapprocher pour l'attaquer

}
