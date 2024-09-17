#include <iostream>
#include "State.h"
#include "StateMachine.h"

StateMachine::StateMachine() :
	m_currentState(nullptr),
	m_isInit(false)
{
}

void StateMachine::Init(std::vector<State*>& states)
{
	if (m_isInit)
	{
		return;
	}
	std::cout << "Init State Machine" << std::endl;
	m_isInit = true;
	m_states = states;
	m_currentState = m_states[0];
	m_currentState->OnEnter();
}

void StateMachine::SwitchToState(State* state)
{
	int numState = std::count(m_states.begin(), m_states.end(), state);
	if (numState <= 0 || state == m_currentState)
	{
		return;
	}
	m_currentState->OnExit();
	m_currentState = state;
	m_currentState->OnEnter();
}

void StateMachine::SwitchToState(int index)
{
	if (index >= m_states.size() || index < 0)
	{
		return;
	}
	State* newState = m_states[index];
	if (newState == m_currentState)
	{
		return;
	}
	m_currentState->OnExit();
	m_currentState = newState;
	m_currentState->OnEnter();
}
