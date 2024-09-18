#include "IAGolemBrain.h"
#include "Mob.h"
#include "Vector2.h"
#include "Hero.h"

using namespace Maths;

void IAGolemBrain::Execute(Mob* possessedMob)
{
	Vector2 mobPos = *possessedMob->GetPosition();
	Vector2 playerPos = *possessedMob->GetHeroTarget()->GetPosition();


	int distance = Vector2::GetDistance(mobPos, playerPos);
	if (distance > 1)
	{
		MoveEvent();
	}

	mobPos = *possessedMob->GetPosition();
	distance = Vector2::GetDistance(mobPos, playerPos);
	if (distance == 1)
	{
		AttackEvent();
	}
}
