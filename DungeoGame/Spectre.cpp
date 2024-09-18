#include "Spectre.h"
#include "Hero.h"

Spectre::Spectre() :
	Mob::Mob()
{

}

Spectre::Spectre(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'S', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Faible
}

void Spectre::Move()
{
	Maths::Vector2* pos = GetPosition();
	Maths::Vector2 newPos = GetNewPosition();

	if (*pos != newPos)
	{
		*pos = newPos;
		OnMove();
	}
}

Maths::Vector2 Spectre::GetNewPosition()
{
	Maths::Vector2 newPos = Maths::Vector2(0, 0);
	int maxDist = 0;

	for (Maths::Vector2 pos : GetMovePosPossibility())
	{
		int dist = Maths::Vector2::GetDistance(pos, *GetHeroTarget()->GetPosition());
		if (maxDist < dist)
		{
			newPos = pos;
			maxDist = dist;
		}
	}

	return newPos;
}

void Spectre::ExecuteCapacity()
{
	//Fuit dans la direction opposée pour éviter le héros

}