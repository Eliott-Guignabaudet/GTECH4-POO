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

	std::vector<std::vector<char>> m_tabCharGame;
	std::vector<std::string> m_tabStringStatistics;

	int m_maxWidthDungeon;
	int m_widthDungeon;
	int m_heightDungeon;
	int m_dungeonRoom;

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

	void InitStatistics();
	void InitTabChar();
	void ReplaceEntity();
	void DrawTabChar();

	std::string DrawOffset(int offset = 0);
	std::string DrawLineTitle(char Char, std::string message);
	std::string DrawLineElement(char Char, std::string message1, std::string message2);
	std::string DrawLineWithNothing(char Char);
	std::string DrawLineWithAnything(char Char);

#pragma endregion

};

