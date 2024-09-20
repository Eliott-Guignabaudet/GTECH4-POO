#include "Golem.h"
#include "Hero.h"

Golem::Golem() :
	Mob::Mob(),
	m_haveCancelDamage(false),
	m_attackRewardUpgrade(0),
	m_cancelDamageRate(25)
{
	m_name = "Golem";
}

Golem::Golem(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'G', maxLife, attackDamage, sizeCanMove, cooldown, hero), 
	m_haveCancelDamage(false),
	m_cancelDamageRate(25)
{
	//Attaque : Moyennement puissante
	m_name = "Golem";
	SetPercentReward(50);
	m_attackRewardUpgrade = (GetAttackDamage() * GetPercentReward() / 100);
	std::string capacity = "+" + std::to_string(m_attackRewardUpgrade) + " attack player";
	SetCapacityTxt(capacity);
}


void Golem::Move()
{
	Mob::Move();
	SendMessage("Move");
}

Vector2 Golem::GetNewPosition(int sizeCanMove)
{
	Vector2 posPlayer = GetHeroTarget()->GetPosition();
	int dist = Vector2::GetDistance(GetPosition(), posPlayer);

	std::vector<Vector2> possibilitiesMoved = GetMovePosPossibility();

	std::vector<Vector2> listPos = std::vector<Vector2>();

	if (dist - 1 <= GetSizeMove())
	{
		Vector2 nearPlayer = GoNearPlayer(sizeCanMove);
		if (nearPlayer != GetPosition()) {
			return nearPlayer;
		}

		return GoToPlayer(sizeCanMove);
	}

	int id = std::rand() % possibilitiesMoved.size();
	return possibilitiesMoved[id];
}

void Golem::ExecuteCapacity()
{
	float randomValue = rand() % 100 + 1;
	if (randomValue <= m_cancelDamageRate)
	{
		m_haveCancelDamage = true; 
		SendMessage("use its capacity !");
		return;
	}
	m_haveCancelDamage = false;
	//Capacité spéciale : Peut résister totalement à l’attaque du héros

}

void Golem::GetKillRewards()
{
	GetHeroTarget()->UpgradeAttack(m_attackRewardUpgrade);
}

void Golem::TakeDamage(int damage, Fighter* fighter)
{
	if (!dynamic_cast<Hero*>(fighter))
	{
		Mob::TakeDamage(damage, fighter); 
		return;
	}
	ExecuteCapacity();
	if (m_haveCancelDamage)
	{
		return;
	}
	Mob::TakeDamage(damage, fighter);
}
