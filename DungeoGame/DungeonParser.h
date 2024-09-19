#pragma once
#include <vector>
#include <string>

enum class EntityType
{
	None = 0,
	Mower = 1,
	Spectre = 2,
	Golem = 3,
	Hero = 4,
};

struct DungeonData
{
public:
	int Width;
	int Height;
	std::vector<EntityType> Entities;
};

class DungeonParser
{
private:
	EntityType GetEntityType(char value);

public:
	static DungeonData ParseDungeon(std::string path);
};

