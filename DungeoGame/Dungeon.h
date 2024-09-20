#pragma once
#include <Windows.h>
#include <vector>
#include "Vector2.h"
#include <iostream>

class Fighter;
class Hero;
class Mob;
struct DungeonData;
struct Message;

class Dungeon
{

public:

#pragma region Variables

	Message* m_message;
	Hero* m_heroPtr;

	std::vector<Fighter*> m_fightersPtr;
	std::vector<std::vector<char>> m_tabCharGame;

	int m_widthWithOffsetDungeon;
	int m_heightWithOffsetDungeon;

	int m_widthDungeon;
	int m_heightDungeon;

	int m_dungeonRoom;
	int m_currentTurn;

#pragma endregion

#pragma region Getteur / Setteur

#pragma endregion

#pragma region Class function

	Dungeon();
	Dungeon(int width, int height);

	void InitWithData(const DungeonData& data);
	void Clear();
	void AddFighter(Fighter* entity);
	void RemoveFighters();

	void SpawnPlayer(int x, int y);
	void SpawnMob(int nbMob = 10);
	Mob* GetRandomMob(Maths::Vector2 randomPos);
	void UpdateMovePossibility(Fighter* fighter);
	void UpdateNearFighterPlayer();
	void HandleOnAttackAllFighters(Fighter* origin);

	char FillBoundsOrDefaultChar(bool xlimit, bool ylimit);
	void Draw();

	void InitTabChar();
	void ReplaceEntity();
	std::vector<std::string>* GetDungeonString();

#pragma endregion

};

