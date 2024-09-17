#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include "App.h"

int main()
{
    std::cout << "Hello World!\n";
    App::GetInstance()->Run();
}
