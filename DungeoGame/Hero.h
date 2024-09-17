#pragma once
#include "Fighter.h"
class Hero :
	public Fighter
{

public:

#pragma region Class function

	Hero();
	Hero(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove);

#pragma endregion
};

