#include "IAController.h"
#include "Mob.h"

void IAController::PossessFighter(Fighter* fighter)
{
	Mob* mob = dynamic_cast<Mob*>(fighter);
	if (!mob)
	{
		return;
	}
	Controller::PossessFighter(mob);
}

void IAController::Execute()
{
	// TODO : Execute IA Brain
}
