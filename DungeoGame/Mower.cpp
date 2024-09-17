#include "Mower.h"

Mower::Mower()
{
	Mob::Mob();
}

Mower::Mower(Maths::Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown)
{
	//Attaque : Tr�s puissante
	Mob::Mob(pos, 'F', maxLife, attackDamage, sizeCanMove, cooldown);
}

void Mower::ExecuteCapacity()
{
	//Capacit� sp�ciale : Se d�place vers le h�ros, cherchant � se rapprocher pour l'attaquer
	Mob::ExecuteCapacity();
}
