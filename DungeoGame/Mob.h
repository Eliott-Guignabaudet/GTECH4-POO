#pragma once
#include "Fighter.h"

class Hero;

class Mob :
    public Fighter
{
private:

#pragma region Variables

    Hero* m_targetPlayer;
    int m_cooldown;

#pragma endregion

public:

#pragma region Getteur / Setteur

	void SetHeroTarget(Hero* target);
    Hero* GetHeroTarget();

#pragma endregion

#pragma region Class function

    Mob();
    Mob(Maths::Vector2* pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* target = nullptr);

    virtual Maths::Vector2 GetNewPosition() = 0;
    virtual void ExecuteCapacity() = 0;

#pragma endregion
};

