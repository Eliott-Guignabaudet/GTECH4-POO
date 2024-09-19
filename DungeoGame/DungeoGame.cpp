#include <iostream>
#include "App.h"
#include "DungeonParser.h"

int main()
{
    std::cout << "Hello World!\n";
    //DungeonParser::ParseDungeon("DungeonMap.txt");
    App::GetInstance()->Run();
}
