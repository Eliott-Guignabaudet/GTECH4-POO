#pragma once
#include <functional>
class Mob;

class IABrain
{
public:
	std::function<void()> ExecuteCapacityEvent;
	std::function<void()> AttackEvent;
	std::function<void()> MoveEvent;

	virtual void Execute( Mob* possessed);
};

