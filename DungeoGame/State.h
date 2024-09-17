#pragma once
class State
{
public:
	virtual void OnEnter();
	virtual void Execute();
	virtual void OnExit();

};

