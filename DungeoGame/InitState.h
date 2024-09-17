#pragma once
#include "State.h"
class InitState :
    public State
{
public:
    virtual void OnEnter() override;
    virtual void Execute() override;
    virtual void OnExit() override;
};

