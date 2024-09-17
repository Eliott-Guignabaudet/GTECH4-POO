#pragma once
#include "State.h"
class GameOverState :
    public State
{
public:
    virtual void OnEnter() override;
    virtual void Execute() override;
    virtual void OnExit() override;
};

