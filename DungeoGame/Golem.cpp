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
	Vector2 posPlayer = GetHeroTarget()->GetPosition();
	int dist = Vector2::GetDistance(GetPosition(), posPlayer);

	std::vector<Vector2> possibilitiesMoved = GetMovePosPossibility();

	if (dist - 1 <= GetSizeMove()) 
	{
		for (Vector2 posMoved : possibilitiesMoved)
		{
			if (Vector2::GetDistance(posMoved, posPlayer) == 1) 
			{
				return posMoved;
			}
		}
	}

	int id = std::rand() % possibilitiesMoved.size();
	return possibilitiesMoved[id];
}

void Golem::ExecuteCapacity()
{
	//Capacité spéciale : Peut résister totalement à l’attaque du héros

}
