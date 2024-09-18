#include "IAController.h"
#include "Mob.h"
#include "IABrain.h"



void IAController::Init(IABrain* iaBrain)
{
	if (iaBrain == nullptr)
	{
		return;
	}
	m_iaBrain = iaBrain;
	
	auto execCapacityBind =
		std::bind(&IAController::HandleExecuteCapacityEvent, this);
	auto attackEventBind =
		std::bind(&IAController::HandleAttackEvent, this);

	m_iaBrain->AttackEvent = attackEventBind;
	m_iaBrain->ExecuteCapacityEvent = execCapacityBind;


}

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
	//TODO : Remove comment when targetplayer is hero (or fighter)
	//m_iaBrain->Execute(GetMobCasted()->m_targetPlayer);
}

Mob* IAController::GetMobCasted()
{
	return dynamic_cast<Mob*>(m_possessedFighter);
}

void IAController::HandleExecuteCapacityEvent()
{
	if (Mob* mob = GetMobCasted())
	{
		mob->ExecuteCapacity();
	}
}

void IAController::HandleAttackEvent()
{
	if (Mob* mob = GetMobCasted())
	{
		//TODO : Remove comment when targetplayer is hero (or fighter)
		//mob->Attack(mob->m_targetPlayer);
	}
}

