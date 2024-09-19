#pragma once
#include "Fighter.h"
#include "Vector2.h"

class Hero;

class Mob :
    public Fighter
{
private:

#pragma region Variables

    Hero* m_targetPlayer;
    int m_cooldown;

    Vector2 m_nearPoses[4];

#pragma endregion

public:

#pragma region Getteur / Setteur

	void SetHeroTarget(Hero* target);
    Hero* GetHeroTarget();

    void SetNearPos(Vector2 pos);
    Vector2* GetNearPos();

#pragma endregion

#pragma region Class function

    Mob();
    Mob(Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* target = nullptr);

    Vector2 GoToPlayer(int sizeCanMove = 0);
    Vector2 GoNearPlayer(int sizeCanMove = 0);
    virtual void Move() override;
    virtual Vector2 GetNewPosition(int sizeCanMove = 0) = 0;
    virtual void ExecuteCapacity() = 0;
    virtual void GetKillRewards() = 0;

    virtual void Die() override;

#pragma endregion
};

