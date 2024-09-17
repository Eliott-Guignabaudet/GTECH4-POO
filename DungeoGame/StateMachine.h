#pragma once
#include <vector>

class State;

class StateMachine
{
private:
	std::vector<State*> m_states;
	State* m_currentState;
	bool m_isInit;
public:
	StateMachine();
	
	void Init(std::vector<State*>& m_states);
	void SwitchToState(State* state);
	void SwitchToState(int index);

	template<typename T>
	T* GetState();
};

template <typename T>
T* StateMachine::GetState() 
{
	for (int i = 0; i < m_states.size(); i++)
	{
		if (T* state = dynamic_cast<T*>(m_states[i]))
		{
			return state;
		}
	}
}

