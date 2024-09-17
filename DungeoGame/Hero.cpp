#include "Hero.h"

Hero::Hero() :
	Fighter::Fighter()
{

}

Hero::Hero(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove) :
	Fighter::Fighter(pos, '@', maxLife, attackDamage, sizeCanMove)
{

}
