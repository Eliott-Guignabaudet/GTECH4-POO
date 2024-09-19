#include <iostream>
#include "App.h"
#include "DungeonParser.h"

int main()
{
    std::cout << "Hello World!\n";
    //DungeonData data = DungeonParser::ParseDungeon("DungeonMap.txt");
    App::GetInstance()->Run();
}
