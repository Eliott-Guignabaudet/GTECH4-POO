#include "Hero.h"

Hero::Hero()
{
	Fighter::Fighter();
}

Hero::Hero(int maxLife, int attackDamage, int sizeCanMove, Maths::Vector2 pos)
{
	Fighter::Fighter(pos, '@', maxLife, attackDamage, sizeCanMove);
}
