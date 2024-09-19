#pragma once
#include <vector>
#include <functional>
#include "State.h"
class IAController;

class IATurnState :
    public State
{
public:
    virtual void OnEnter() override;
    virtual void Execute() override;
    virtual void OnExit() override;
    
    std::function<void()> OnIAControllerFinish;
    std::function<void()> OnFinishIATurn;
private:
    bool m_isTurnFinish;
    float m_elapsedTimeBeforeLastExecution;
    int m_currentIAIndex;
    std::vector<IAController*> m_currentIAs;

    void SetActiveIas(bool isActive);
    std::vector<IAController*> GetIAsControllers();
};

