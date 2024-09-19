#pragma once
#include "Fighter.h"

class Hero :
	public Fighter
{

public:
	std::vector<Fighter*> m_nearPos;

#pragma region Class function

	Hero();
	Hero(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove);

	virtual void Move() override;
	void SetNearPosPlayer(const std::vector<Fighter*>& fighters);
	std::vector<Fighter*>& GetNearFightPlayer();

#pragma endregion
};

