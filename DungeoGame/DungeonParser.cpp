#include "DungeonParser.h"
#include <fstream>
#include <iostream>

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

DungeonData DungeonParser::ParseDungeon(std::string path)
{
    std::fstream newFile;
    newFile.open(path, std::ios::in);
    if (!newFile.is_open())
    {
        return DungeonData();
    }

    std::vector<std::string> lines;

    std::string content;
    while (std::getline(newFile, content)) 
    {
        lines.push_back(content);
    }
    int lineSize = lines[0].size();
    std::vector<int> nonValidIndexs;
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].length()!= lineSize)
        {
            nonValidIndexs.push_back(i);
            std::cout << "La ligne: " << i << " n'est pas valide\n";
            std::cout << "Valeur attendue: " << lineSize << '\n';
            std::cout << "Valeur récupéré:" << lines[i].length() << std::endl << std::endl;
        }
    }

    newFile.close();
    return DungeonData();
}
