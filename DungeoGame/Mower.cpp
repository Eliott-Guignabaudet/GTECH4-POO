#include "Mower.h"
#include "Hero.h"
#include "Fighter.h"

std::function<void(Fighter*)> Mower::OnAttackAllFighter;

Mower::Mower() :
	Mob::Mob()
{

}

Mower::Mower(Vector2 pos, int maxLife, int attackDamage, int sizeCanMove, int cooldown, Hero* hero) :
	Mob::Mob(pos, 'F', maxLife, attackDamage, sizeCanMove, cooldown, hero)
{
	//Attaque : Très puissante
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
}

void Mower::GetKillRewards()
{
	if (OnAttackAllFighter) 
	{
		OnAttackAllFighter(this);
	}
}
