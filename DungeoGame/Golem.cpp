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


Vector2 Golem::GetNewPosition(int sizeCanMove)
{
	if (sizeCanMove == 0)
	{
		sizeCanMove = GetSizeMove();
	}
	Vector2 posPlayer = GetHeroTarget()->GetPosition();
	int dist = Vector2::GetDistance(GetPosition(), posPlayer);

	std::vector<Vector2> possibilitiesMoved = GetMovePosPossibility();

	std::vector<Vector2> listPos = std::vector<Vector2>();

	if (dist - 1 <= GetSizeMove())
	{
		Vector2 nearPlayer = GoNearPlayer(sizeCanMove);
		if (nearPlayer != GetPosition()) {
			return nearPlayer;
		}

		return GoToPlayer(sizeCanMove);
	}

	int id = std::rand() % possibilitiesMoved.size();
	return possibilitiesMoved[id];
}

void Golem::ExecuteCapacity()
{
	//Capacité spéciale : Peut résister totalement à l’attaque du héros

}
