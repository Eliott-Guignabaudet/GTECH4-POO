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

	void SetNearPosPlayer(const std::vector<Fighter*>& fighters);
	std::vector<Fighter*>& GetNearFightPlayer();

	void HealPlayer();
	void UpgradeAttack(int upgrade);
	void AttackAround();
	virtual void Move() override;
	virtual void Die() override;

#pragma endregion
};

