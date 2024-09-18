#include "IABrain.h"
#include "Mob.h"

void IABrain::Execute(Mob* possessed)
{
}

bool IABrain::ExecuteEvent(std::function<void()> event)
{
	if (event)
	{
		event();
		return true;
	}
	return false;
}
