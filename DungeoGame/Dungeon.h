#pragma once
#include <Windows.h>
#include <vector>
#include "Vector2.h"
#include <iostream>

class Fighter;
class Hero;
class Mob;
struct DungeonData;

class Dungeon
{

public:

#pragma region Variables

	CONSOLE_SCREEN_BUFFER_INFO* m_csbi;
	Hero* m_heroEntity;
	std::vector<Fighter*> m_fighters;

	std::vector<std::vector<char>> m_tabChar;

	int m_maxWidthDungeon;
	int m_widthDungeon;
	int m_heightDungeon;

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
	int GetConsoleWidthSize();
	void HandleOnAttackAllFighters(Fighter* origin);

	char FillBoundsOrDefaultChar(bool xlimit, bool ylimit);
	void Draw();

	void InitTabChar();
	void ReplaceEntity();
	void DrawTabChar();

	void DrawStatistics();
	void DrawOffset(int offset = 0);
	void DrawOffsetRight(int offset = 0);
	void DrawOffsetLeft(int offset = 0);
	void DrawLineTitle(char Char, std::string message);
	void DrawLineElement(char Char, std::string message1, std::string message2);
	void DrawLineWithNothing(char Char);
	void DrawLineWithAnything( char Char);

#pragma endregion

};

