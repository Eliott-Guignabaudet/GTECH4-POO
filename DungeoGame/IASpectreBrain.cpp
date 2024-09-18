#include "IASpectreBrain.h"
#include "Spectre.h"
#include "Vector2.h"
#include "Hero.h"

using namespace Maths;

void IASpectreBrain::Execute(Mob* possessedMob)
{
	if (CapacityEvent)
	{
		CapacityEvent();
	}

	Vector2 mobPos = *possessedMob->GetPosition();
	Vector2 playerPos = *possessedMob->GetHeroTarget()->GetPosition();

	int distance = Vector2::GetDistance(mobPos, playerPos);
	if (distance == 1)
	{
		if (AttackEvent)
		{
			AttackEvent();
		}
	}
}
