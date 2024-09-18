#pragma once
#include <functional>
class Mob;

class IABrain
{
public:
	std::function<void()> CapacityEvent;
	std::function<void()> AttackEvent;
	std::function<void()> MoveEvent;


	virtual void Execute( Mob* possessed);

	bool ExecuteEvent(std::function<void()> event);
};

