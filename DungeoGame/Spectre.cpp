#include "Spectre.h"

Spectre::Spectre()
{
	Mob::Mob();
}

Spectre::Spectre(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown) :
	Mob::Mob(pos, 'S', maxLife, attackDamage, sizeCanMove, cooldown)
{
	//Attaque : Faible
}

void Spectre::ExecuteCapacity()
{
	//Fuit dans la direction opposée pour éviter le héros
	Mob::ExecuteCapacity();
}