#pragma once
#include "Entity.h"
#include <functional>
#include <vector>

class Fighter :
	public Entity
{
private:

#pragma region Variables

	Vector2 m_dir;

	std::vector<Vector2> m_listPosPossibilities;

	int m_life;
	int m_maxLife;

	int m_attackDamage;
	int m_sizeCanMove;
protected:
	void EventSendMessage(std::string message);

public :

	bool m_isDead;
	bool isHisTurn;
	static std::function<void(Fighter*)> OnRedrawMoveFighter;
	static std::function<void(std::string)> OnFighterSendActionMessage;
	std::function<void()> OnDie;

#pragma endregion

#pragma region Getteur / Setteur

	void SetDirection(Vector2& dir);
	Vector2& GetDirection();

	void SetMaxLife(int maxLife);
	int GetMaxLife();
	int GetLife();

	//void SetHealth(int health);

	void SetAttackDamage(int attackDamage);
	int GetAttackDamage();

	void SetSizeMove(int sizeCanMove);
	int GetSizeMove();

#pragma endregion

#pragma region Class function

	Fighter();
	Fighter(Vector2 pos, char sprite, int maxLife, int attackDamage, int sizeCanMove);

	void SetMovePosPossibility(int xLimit, int Ylimit);
	void SetRemoveFighterPosPossibility(std::vector<Fighter*>* fighters);
	std::vector<Vector2> GetMovePosPossibility();

	virtual void Move();
	void OnRedrawMovePossibilities();
	void Attack(Fighter* target);
	virtual void TakeDamage(int damage, Fighter* origin = nullptr);
	virtual void Die();

#pragma endregion
};