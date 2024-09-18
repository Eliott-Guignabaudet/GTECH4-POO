#include "Golem.h"
#include "Hero.h"

Golem::Golem() :
	Mob::Mob()
{

}

Golem::Golem(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'G', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Moyennement puissante
}

void Golem::Move()
{
	Maths::Vector2* pos = GetPosition();
	Maths::Vector2 newPos = GetNewPosition();

	if (*pos != newPos) 
	{
		*pos = newPos;
		OnMove();
	}
}

Maths::Vector2 Golem::GetNewPosition()
{
	std::vector<Maths::Vector2> possibilitiesMoved = GetMovePosPossibility();
	for (Maths::Vector2 pos : possibilitiesMoved)
	{
		if (*GetHeroTarget()->GetPosition() == pos)
		{
			return pos;
		}
	}

	int id = std::rand() % possibilitiesMoved.size();
	return possibilitiesMoved[id];
}

void Golem::ExecuteCapacity()
{
	//Capacité spéciale : Peut résister totalement à l’attaque du héros

}
