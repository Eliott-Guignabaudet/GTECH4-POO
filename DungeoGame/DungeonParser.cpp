#include "DungeonParser.h"
#include <fstream>
#include <iostream>

std::vector<std::string> DungeonParser::GetLines(std::fstream& file)
{
    std::vector<std::string> lines;

    std::string content;
    while (std::getline(file, content))
    {
        lines.push_back(content);
    }
    file.close();
    return lines;
}

bool DungeonParser::GetIsLinesValid(std::vector<std::string> lines)
{
    int lineSize = lines[0].size();
    bool isLineValid = true;
    std::vector<int> nonValidIndexs;
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].length() != lineSize)
        {
            isLineValid = false;
            nonValidIndexs.push_back(i);
            std::cout << "La ligne: " << i << " n'est pas valide\n";
            std::cout << "Valeur attendue: " << lineSize << '\n';
            std::cout << "Valeur récupéré:" << lines[i].length() << std::endl << std::endl;
        }
    }
    return isLineValid;
}

EntityType DungeonParser::GetEntityType(char value)
{
    switch (value)
    {
    case '@':
        return EntityType::Hero;
    case 'F':
        return EntityType::Mower;
    case 'S':
        return EntityType::Spectre;
    case 'G':
        return EntityType::Golem;

    default:
        return EntityType::None;
    }
}

std::vector<EntityData> DungeonParser::GetEntities(std::vector<std::string> lines)
{
    std::vector<EntityData> result;
    for (int i = 1; i < lines.size() - 1; i++)
    {
        for (int j = 1; j < lines[0].size() - 1; j++)
        {
            EntityType entityType = GetEntityType(lines[i][j]);
            if (entityType == EntityType::None)
            {
                continue;
            }
            EntityData entityData;
            entityData.Type = entityType;
            entityData.Position = Maths::Vector2(j - 2, i );
            result.push_back(entityData);
        }
    }
    return result;
}





DungeonData DungeonParser::ParseDungeon(std::string path)
{
    DungeonData dungeonData;
    std::fstream newFile;
    newFile.open(path, std::ios::in);
    if (!newFile.is_open())
    {
        return dungeonData;
    }

    std::vector<std::string> lines = GetLines(newFile);
    bool isLineValid = GetIsLinesValid(lines);
    if (!isLineValid)
    {
        return dungeonData;
    }
    
    dungeonData.Width = lines[0].size() - 5;
    dungeonData.Height = lines.size() - 1;

    dungeonData.Entities = GetEntities(lines);


    return dungeonData;
}
