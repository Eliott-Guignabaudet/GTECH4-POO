#include "Golem.h"

Golem::Golem()
{
	Mob::Mob();
}

Golem::Golem(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown) :
	Mob::Mob(pos, 'G', maxLife, attackDamage, sizeCanMove, cooldown)
{
	//Attaque : Moyennement puissante
}

void Golem::ExecuteCapacity()
{
	//Capacit� sp�ciale : Peut r�sister totalement � l�attaque du h�ros
	Mob::ExecuteCapacity();
}
