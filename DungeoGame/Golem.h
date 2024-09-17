#pragma once
#include "Mob.h"

class Golem :
    public Mob
{

public:

#pragma region Class function

    Golem();
    Golem(Maths::Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown);

    virtual void ExecuteCapacity() override;

#pragma endregion

};

