#include "Mower.h"

Mower::Mower()
{
	Mob::Mob();
}

Mower::Mower(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown) :
	Mob::Mob(pos, 'F', maxLife, attackDamage, sizeCanMove, cooldown)
{
	//Attaque : Très puissante
}

void Mower::ExecuteCapacity()
{
	//Capacité spéciale : Se déplace vers le héros, cherchant à se rapprocher pour l'attaquer
	Mob::ExecuteCapacity();
}
