#pragma once
#include <vector>
#include <string>
#include "Vector2.h"

enum class EntityType
{
	None = 0,
	Mower = 1,
	Spectre = 2,
	Golem = 3,
	Hero = 4,
};

struct EntityData
{
	Maths::Vector2 Position;
	EntityType Type;
};

struct DungeonData
{
public:
	int Width;
	int Height;
	std::vector<EntityData> Entities;
};

class DungeonParser
{
private:
	static std::vector<std::string> GetLines(std::fstream& file);
	static bool GetIsLinesValid(std::vector<std::string> lines);
	static EntityType GetEntityType(char value);
	static std::vector<EntityData> GetEntities(std::vector<std::string> lines);
public:
	static DungeonData ParseDungeon(std::string path);
};

