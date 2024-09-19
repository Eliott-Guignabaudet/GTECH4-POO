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

	int dist = Vector2::GetDistance(posMower, posPlayer);
	std::vector<Vector2> listPos = std::vector<Vector2>();

	if (dist - 1 <= GetSizeMove())
	{
		for (Vector2 pos : GetMovePosPossibility())
		{
			if (Vector2::GetDistance(pos, posPlayer) == 1)
			{
				listPos.push_back(pos);
			}
		}

		if (!listPos.empty()) 
		{
			int id = std::rand() % listPos.size();
			return listPos[id];
		}
	}

	int minDist = INT_MAX;

	for (Vector2 pos : GetMovePosPossibility())
	{
		int dist = Vector2::GetDistance(pos, posPlayer);
		if (minDist > dist)
		{
			minDist = dist;
			listPos.clear();
			listPos.push_back(pos);
		}
		else if(minDist == dist)
		{
			listPos.push_back(pos);
		}
	}

	if (!listPos.empty())
	{
		int id = std::rand() % listPos.size();
		return listPos[id];
	}

	return posMower;
}

void Mower::ExecuteCapacity()
{
	//Capacité spéciale : Se déplace vers le héros, cherchant à se rapprocher pour l'attaquer
	Move();
}
