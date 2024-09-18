#pragma once
#include <vector>
#include "Vector2.h"
#include <iostream>

class Fighter;
class Hero;
class Mob;

class Dungeon
{

public:

#pragma region Variables

	Hero* m_heroEntity;
	std::vector<Fighter*> m_fighters;

	int m_widthDungeon;
	int m_heightDungeon;

#pragma endregion

#pragma region Getteur / Setteur

#pragma endregion

#pragma region Class function

	Dungeon();
	Dungeon(int width, int height);

	void Clear();
	void AddFighter(Fighter* entity);
	void RemoveFighter(Fighter* entity);

	void SpawnPlayer(int x, int y);
	void SpawnMob(int nbMob = 10);
	Mob* GetRandomMob(Maths::Vector2* randomPos);

	char FillBoundsOrDefaultChar(bool xlimit, bool ylimit);
	void Draw();

	void InitTabChar(std::vector<std::vector<char>>* tabChar);
	void ReplaceEntity(std::vector<std::vector<char>>* tabChar);
	void DrawTabChar(std::vector<std::vector<char>>* tabChar);

	void DrawStatistics();
	void DrawLineTitle(int size, char Char, std::string message);
	void DrawLineElement(int size, char Char, std::string message1, std::string message2);
	void DrawLineWithNothing(int size, char Char);
	void DrawLineWithAnything(int size, char Char);

#pragma endregion

};

