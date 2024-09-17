#pragma once
#include <vector>
#include "Entity.h"

class Dungeon
{

public:

#pragma region Variables

	Entity* m_defaultEntity;
	std::vector<Entity*> m_entities;

	int m_weightDungeon;
	int m_heightDungeon;

	char m_cornerWall;
	char m_horizontalWall;
	char m_verticalWall;

#pragma endregion

#pragma region Getteur / Setteur

#pragma endregion

#pragma region Class function

	Dungeon();
	Dungeon(int weight, int height, char cornerWall = '*', char horizontalWall = '-', char verticalWall = '|');

	void Clear();
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	bool DrawLimitBounds(bool xlimit, bool ylimit);
	void Draw();

#pragma endregion

};

