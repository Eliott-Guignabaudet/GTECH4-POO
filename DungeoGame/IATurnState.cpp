#include "IATurnState.h"
#include "App.h"
#include "IAController.h"
#include "Time.h"

const float TIME_BETWEEN_IA_EXECUTION = 1.f;

void IATurnState::OnEnter()
{
	m_currentIAs = GetIAsControllers();
	SetActiveIas(true);
	m_isTurnFinish = false;
	m_elapsedTimeBeforeLastExecution = 0.f;
	m_currentIAIndex;
}

void IATurnState::Execute()
{
	if (m_isTurnFinish)
	{
		return;
	}
	if (m_currentIAIndex >= m_currentIAs.size() 
		&& m_elapsedTimeBeforeLastExecution >= TIME_BETWEEN_IA_EXECUTION)
	{
		m_isTurnFinish = true;
		if (OnFinishIATurn)
		{
			OnFinishIATurn();
		}
		return;
	}
	
	if (m_currentIAIndex < m_currentIAs.size() && 
		m_elapsedTimeBeforeLastExecution >= TIME_BETWEEN_IA_EXECUTION)
	{
		m_currentIAs[m_currentIAIndex]->Execute();
		m_currentIAIndex++;
		m_elapsedTimeBeforeLastExecution = 0.f;
	}

	m_elapsedTimeBeforeLastExecution += 
		Time::GetInstance()->GetScaledDeltaTime();
}

void IATurnState::OnExit()
{
	SetActiveIas(false);
}

void IATurnState::SetActiveIas(bool isActive)
{
	for (int i = 0; i < m_currentIAs.size(); i++)
	{
		m_currentIAs[i]->SetActive(isActive);
	}
}

std::vector<IAController*> IATurnState::GetIAsControllers()
{
	return App::GetInstance()->GetIasControllers();;
}
