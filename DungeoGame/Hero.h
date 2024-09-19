#pragma once
#include "Fighter.h"

class Hero :
	public Fighter
{

public:
	std::vector<Entity*> nearPos;

#pragma region Class function

	Hero();
	Hero(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove);

	virtual void Move() override;
	void SetNearPosPlayer(std::vector<Fighter*>* fighters);
	std::vector<Entity*>& GetNearEntityPlayer();

#pragma endregion
};

