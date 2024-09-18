#include "IAController.h"
#include "Mob.h"
#include "IABrain.h"
#include "Hero.h"


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
	auto moveEventBind =
		std::bind(&IAController::HandleMoveEvent, this);

	m_iaBrain->AttackEvent = attackEventBind;
	m_iaBrain->CapacityEvent = execCapacityBind;
	m_iaBrain->MoveEvent = moveEventBind;


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
	m_iaBrain->Execute(GetMobCasted());
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
		mob->Attack(mob->GetHeroTarget());
	}
}

void IAController::HandleMoveEvent()
{
	m_possessedFighter->Move();
}

