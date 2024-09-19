#include "IATurnState.h"
#include "App.h"
#include "IAController.h"
#include "Time.h"

const float TIME_BETWEEN_IA_EXECUTION = 0.5f;

void IATurnState::OnEnter()
{
	m_currentIAs = GetIAsControllers();
	SetActiveIas(true);
	m_isTurnFinish = false;
	m_elapsedTimeBeforeLastExecution = 0.f;
	m_currentIAIndex = 0;
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
	bool isIndexOutOfVector = m_currentIAIndex >= m_currentIAs.size();

	if (!isIndexOutOfVector && (m_currentIAs[m_currentIAIndex] == nullptr
		|| !m_currentIAs[m_currentIAIndex]->IsValid()))
	{
		App::GetInstance()->RemoveIAController(m_currentIAs[m_currentIAIndex]);
		m_currentIAIndex++;
		m_elapsedTimeBeforeLastExecution = 0.f;
		return;
	}
	
	if (!isIndexOutOfVector && m_elapsedTimeBeforeLastExecution >= TIME_BETWEEN_IA_EXECUTION)
	{
		m_currentIAs[m_currentIAIndex]->Execute();
		m_currentIAIndex++;
		m_elapsedTimeBeforeLastExecution = 0.f;
		if (OnIAControllerFinish)
		{
			OnIAControllerFinish();
		}
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
