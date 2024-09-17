#pragma once
#include <vector>
#include "Vector2.h"

class Entity;
class Mob;

class Dungeon
{

public:

#pragma region Variables

	Entity* m_heroEntity;
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

	void SpawnPlayer(int x, int y);
	void SpawnMob(int nbMob = 10);
	Mob* GetRandomMob(Maths::Vector2* randomPos);

	bool DrawLimitBounds(bool xlimit, bool ylimit);
	void Draw();

	//void ResizeConsole();
	//void AfficherDimensionsConsole();

#pragma endregion

};

