#pragma once
#include "Controller.h"

class PlayerController :
    public Controller
{
public:
    virtual void PossessFighter(Fighter* fighter) override;
    virtual void Update() override;
};

