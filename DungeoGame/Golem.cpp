#include "Golem.h"
#include "Hero.h"

Golem::Golem() :
	Mob::Mob()
{

}

Golem::Golem(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'G', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Moyennement puissante
}


Vector2 Golem::GetNewPosition()
{
	Vector2 posGolem = GetPosition();
	Vector2 posPlayer = GetHeroTarget()->GetPosition();
	int dist = Vector2::GetDistance(posGolem, posPlayer);

	std::vector<Vector2> possibilitiesMoved = GetMovePosPossibility();

	if (dist - 1 <= GetSizeMove()) 
	{
		std::vector<Entity*> nearPosPlayer = GetHeroTarget()->GetNearEntityPlayer();

		for (Vector2 posMoved : possibilitiesMoved)
		{
			for (Entity* nearPos : nearPosPlayer)
			{
				if (Fighter* fighter = dynamic_cast<Fighter*>(nearPos))
				{
					continue;
				}
				if (nearPos->GetPosition() == posMoved)
				{
					return posMoved;
				}
			}
		}
	}
	else 
	{
		int id = std::rand() % possibilitiesMoved.size();
		posGolem = possibilitiesMoved[id];
	}

	return posGolem;
}

void Golem::ExecuteCapacity()
{
	//Capacité spéciale : Peut résister totalement à l’attaque du héros

}
