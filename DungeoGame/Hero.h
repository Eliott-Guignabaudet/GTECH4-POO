#pragma once
#include "Fighter.h"
class Hero :
	public Fighter
{

public:

#pragma region Class function

	Hero();
	Hero(int maxLife, int attackDamage, int sizeCanMove, Maths::Vector2 pos);

#pragma endregion
};

