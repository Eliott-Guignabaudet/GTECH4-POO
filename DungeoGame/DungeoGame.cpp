#include <iostream>
#include <Windows.h>
#include "App.h"

void GetConsoleSize() 
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Handle de la console
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Récupérer les informations de la console
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;  // Largeur
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Hauteur

        std::cout << "Largeur de la console: " << width << " caractères" << std::endl;
        std::cout << "Hauteur de la console: " << height << " lignes" << std::endl;
    }
    else {
        std::cerr << "Impossible de récupérer les dimensions de la console." << std::endl;
    }
}

int main()
{
    //GetConsoleSize();

    //Sleep(2000);

    //GetConsoleSize();

    std::cout << "Hello World!\n";
    App::GetInstance()->Run();
}
