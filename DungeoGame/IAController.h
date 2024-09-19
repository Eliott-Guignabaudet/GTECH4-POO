#pragma once
#include "Controller.h"
class IABrain;
class Mob;

class IAController :
    public Controller
{
private:
    IABrain* m_iaBrain;

public:
    void Init(IABrain* iaBrain);
    virtual void PossessFighter(Fighter* fighter) override;
    void Execute();
    Mob* GetMobCasted();


    void HandleExecuteCapacityEvent();
    void HandleAttackEvent();
    void HandleMoveEvent();
    void HandleOnFighterDieEvent();
};

