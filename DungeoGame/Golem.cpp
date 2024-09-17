#include "Golem.h"

Golem::Golem()
{
	Mob::Mob();
}

Golem::Golem(Maths::Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown)
{
	//Attaque : Moyennement puissante
	Mob::Mob(pos, 'G', maxLife, attackDamage, sizeCanMove, cooldown);
}

void Golem::ExecuteCapacity()
{
	//Capacit� sp�ciale : Peut r�sister totalement � l�attaque du h�ros
	Mob::ExecuteCapacity();
}
