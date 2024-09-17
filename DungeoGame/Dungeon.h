#pragma once
#include <vector>
#include "Entity.h"

class Dungeon
{

public:

#pragma region Variables

	Entity* m_defaultEntity;
	std::vector<Entity*> m_entities;

	int m_widthDungeon;
	int m_heightDungeon;

#pragma endregion

#pragma region Getteur / Setteur

#pragma endregion

#pragma region Class function

	Dungeon();
	Dungeon(int width, int height);

	void Clear();
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	bool DrawLimitBounds(bool xlimit, bool ylimit);
	void Draw();

	//void ResizeConsole();
	//void AfficherDimensionsConsole();

#pragma endregion

};

