#pragma once
#include "Entity.h"
#include <vector>

class Fighter :
	public Entity
{
public:

#pragma region Variables

	Maths::Vector2 m_dir;

	int m_life;
	int m_maxLife;

	int m_attackDamage;

	int m_sizeCanMove;

#pragma endregion

#pragma region Getteur / Setteur

	void SetDirection(Maths::Vector2& dir);
	Maths::Vector2& GetDirection();

	void SetMaxLife(int maxLife);
	int GetMaxLife();

	//void SetHealth(int health);

	void SetAttackDamage(int attackDamage);
	int GetAttackDamage();

	void SetSizeMove(int sizeCanMove);
	int GetSizeMove();

#pragma endregion

#pragma region Class function

	Fighter();
	Fighter(Maths::Vector2& pos, char sprite, int maxLife, int attackDamage, int sizeCanMove);

	//std::vector<Entity*> NearFighter();
	void Attack(Fighter* target);
	void TakeDamage(int damage);
	virtual void Die();

#pragma endregion
};