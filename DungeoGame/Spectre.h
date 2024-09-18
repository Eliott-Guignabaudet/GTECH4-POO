#pragma once
#include "Mob.h"
class Spectre :
    public Mob
{

public:

#pragma region Class function

    Spectre();
    Spectre(Maths::Vector2* pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero);

    virtual void Move() override;
    virtual Maths::Vector2 GetNewPosition() override;
    virtual void ExecuteCapacity() override;

#pragma endregion

};

