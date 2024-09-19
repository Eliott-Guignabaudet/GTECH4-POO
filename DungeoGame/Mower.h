#pragma once
#include "Mob.h"
class Mower :
    public Mob
{

public:

#pragma region Class function

    Mower();
    Mower(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero);

    virtual Vector2 GetNewPosition() override;
    virtual void ExecuteCapacity() override;

#pragma endregion
};

