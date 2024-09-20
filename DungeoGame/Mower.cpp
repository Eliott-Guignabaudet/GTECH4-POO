#include "Mower.h"
#include "Hero.h"
#include "Fighter.h"

std::function<void(Fighter*)> Mower::OnAttackAllFighter;

Mower::Mower() :
	Mob::Mob()
{
	m_name = "Mower";
}

Mower::Mower(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'F', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Très puissante
	m_name = "Mower";
	SetPercentReward(50);
	std::string capacity = "All mob -" + std::to_string((attackDamage * GetPercentReward()) / 100) + " PV";
	SetCapacityTxt(capacity);
}



Vector2 Mower::GetNewPosition(int sizeCanMove)
{
	Vector2 posMower = GetPosition();
	Vector2 posPlayer = GetHeroTarget()->GetPosition();

	int dist = Vector2::GetDistance(posMower, posPlayer);
	std::vector<Vector2> listPos = std::vector<Vector2>();

	Vector2 nearPlayer = GoNearPlayer(sizeCanMove);
	if (nearPlayer != GetPosition()) {
		return nearPlayer;
	}

	return GoToPlayer(sizeCanMove);
}

void Mower::ExecuteCapacity()
{
	//Capacité spéciale : Se déplace vers le héros, cherchant à se rapprocher pour l'attaquer
	Move();
	EventSendMessage("use its capacity !");

}

void Mower::GetKillRewards()
{
	if (OnAttackAllFighter) 
	{
		SetAttackDamage((GetAttackDamage() * GetPercentReward()) / 100);
		OnAttackAllFighter(this);
	}
}
