#include <iostream>
#include <Windows.h>
#include "App.h"

int main()
{
    std::cout << "Hello World!\n";
    App::GetInstance()->Run();
}
