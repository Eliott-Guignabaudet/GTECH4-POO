#pragma once
#include "Mob.h"
class Mower :
    public Mob
{

public:

#pragma region Class function

    Mower();
    Mower(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero);

    virtual Vector2 GetNewPosition(int sizeCanMove = 0) override;
    virtual void ExecuteCapacity() override;

#pragma endregion
};

