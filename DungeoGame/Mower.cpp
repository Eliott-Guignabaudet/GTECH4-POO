#include "Mower.h"
#include "Hero.h"
#include "Fighter.h"

Mower::Mower() :
	Mob::Mob()
{

}

Mower::Mower(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'F', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Très puissante
}



Vector2 Mower::GetNewPosition()
{
	Vector2 posMower = GetPosition();
	Vector2 posPlayer = GetHeroTarget()->GetPosition();
	int minDist = INT_MAX;

	for (Vector2 pos : GetMovePosPossibility())
	{
		int dist = Vector2::GetDistance(pos, posPlayer);
		if (dist <= 1) 
		{
			std::vector<Entity*> nearEntityPlayer = GetHeroTarget()->GetNearEntityPlayer();

			for (Entity* nearPos : nearEntityPlayer)
			{
				if (Fighter* fighter = dynamic_cast<Fighter*>(nearPos))
				{
					continue;
				}
				else if(pos == nearPos->GetPosition())
				{
					return pos;
				}
			}
		}
		else if (minDist > dist)
		{
			posMower = pos;
			minDist = dist;
		}
	}

	return posMower;
}

void Mower::ExecuteCapacity()
{
	//Capacité spéciale : Se déplace vers le héros, cherchant à se rapprocher pour l'attaquer
	Move();
}
