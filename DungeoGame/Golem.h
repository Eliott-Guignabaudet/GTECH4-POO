#pragma once
#include "Mob.h"

class Golem :
    public Mob
{

public:

#pragma region Class function

    Golem();
    Golem(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero);

    virtual Vector2 GetNewPosition(int sizeCanMove = 0) override;
    virtual void ExecuteCapacity() override;
    virtual void GetKillRewards() override;

#pragma endregion

};

