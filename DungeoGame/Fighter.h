#pragma once
#include "Entity.h"
#include <functional>
#include <vector>

class Fighter :
	public Entity
{
private:

#pragma region Variables

	Maths::Vector2 m_dir;

	std::vector<Maths::Vector2> m_listPosPossible;

	int m_life;
	int m_maxLife;

	int m_attackDamage;

	int m_sizeCanMove;

public :
	static std::function<void(Fighter*)> OnFighterMoved;

#pragma endregion

#pragma region Getteur / Setteur

	void SetDirection(Maths::Vector2& dir);
	Maths::Vector2& GetDirection();

	void SetMaxLife(int maxLife);
	int GetLife();

	//void SetHealth(int health);

	void SetAttackDamage(int attackDamage);
	int GetAttackDamage();

	void SetSizeMove(int sizeCanMove);
	int GetSizeMove();

#pragma endregion

#pragma region Class function

	Fighter();
	Fighter(Maths::Vector2* pos, char sprite, int maxLife, int attackDamage, int sizeCanMove);

	void SetMovePosPossibility(int xLimit, int Ylimit);
	std::vector<Maths::Vector2> GetMovePosPossibility();

	virtual void Move();
	void OnMove();
	void Attack(Fighter* target);
	virtual void TakeDamage(int damage, Fighter* target = nullptr);
	virtual void Die();

	void UpdateMovePossibility(int width, int height);

#pragma endregion
};