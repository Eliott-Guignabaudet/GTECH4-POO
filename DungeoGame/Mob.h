#pragma once
#include "Fighter.h"
class Mob :
    public Fighter
{
public:

#pragma region Variables

    Fighter m_targetPlayer;
    int m_cooldown;

#pragma endregion

#pragma region Getteur / Setteur

	void SetHeroTarget(Fighter target);

#pragma endregion

#pragma region Class function

    Mob();
    Mob(Maths::Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown);

    virtual void ExecuteCapacity();

#pragma endregion
};

