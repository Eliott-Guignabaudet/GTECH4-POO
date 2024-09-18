#pragma once
#include "Controller.h"
class IAController :
    public Controller
{
public:
    virtual void PossessFighter(Fighter* fighter) override;
    void Execute();
};

