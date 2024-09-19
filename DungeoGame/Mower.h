#pragma once
#include "Mob.h"
#include <functional>

class Fighter;

class Mower :
    public Mob
{

public:
    static std::function<void(Fighter*)> OnAttackAllFighter;

#pragma region Class function

    Mower();
    Mower(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero);

    virtual Vector2 GetNewPosition(int sizeCanMove = 0) override;
    virtual void ExecuteCapacity() override;
    virtual void GetKillRewards() override;

#pragma endregion
};

