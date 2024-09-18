#pragma once
#include "State.h"
class IATurnState :
    public State
{
public:
    virtual void OnEnter() override;
    virtual void Execute() override;
    virtual void OnExit() override;
private:
    void SetActiveIas(bool isActive);
};

