#include "Dungeon.h"
#include <iostream>
#include <Windows.h>

const char CORNER_WALL = '*';
const char HORIZONTAL_WALL = '-';
const char VERTICAL_WALL = '|';

Dungeon::Dungeon() :
    m_defaultEntity(nullptr),
    m_widthDungeon(0),
    m_heightDungeon(0)
{

}

Dungeon::Dungeon(int width, int height) :
    m_widthDungeon(width),
    m_heightDungeon(height)
{
    m_defaultEntity = new Entity();
    m_entities = std::vector<Entity*>();
}

void Dungeon::Clear()
{
    for (Entity* entity : m_entities)
    {
        delete entity;
    }

    m_entities.clear();
}

void Dungeon::AddEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void Dungeon::RemoveEntity(Entity* entity)
{
    for (auto it = m_entities.begin(); it != m_entities.end();)
    {
        if (*it == entity)
        {
            delete* it;
            it = m_entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool Dungeon::DrawLimitBounds(bool xlimit, bool ylimit) 
{
    if (xlimit && ylimit)
    {
        std::cout << CORNER_WALL;
    }
    else if (ylimit)
    {
        std::cout << HORIZONTAL_WALL;
    }
    else if (xlimit)
    {
        std::cout << VERTICAL_WALL;
    }
    else 
    {
        return false;
    }
    return true;
}

void Dungeon::Draw()
{
    for (size_t i = 0; i <= m_heightDungeon; i++)
    {
        bool yIsInLimit = (i == 0 || i == m_heightDungeon);

        for (size_t j = 0; j <= m_widthDungeon; j++)
        {
            bool xIsInLimit = (j == 0 || j == m_widthDungeon);

            bool isDrawLimitBounds = DrawLimitBounds(xIsInLimit, yIsInLimit);

            if (!isDrawLimitBounds) 
            {
                bool isDefaultEntity = true;
                for (Entity* entity : m_entities)
                {
                    if (entity->GetPosition() == Maths::Vector2(i, j)) 
                    {
                        isDefaultEntity = false;
                        entity->Draw();
                        break;
                    }
                }

                if (isDefaultEntity) {
                    m_defaultEntity->Draw();
                }
            }
        }
        std::cout << std::endl;
    }
}

//void Dungeon::ResizeConsole() {
//    // R�cup�rer le handle de la console
//    HWND console = GetConsoleWindow();
//
//    // D�finir la nouvelle taille de la fen�tre
//    RECT r;
//    GetWindowRect(console, &r); // R�cup�rer la position actuelle de la fen�tre
//    MoveWindow(console, r.left, r.top, m_widthDungeon, m_heightDungeon, TRUE); // Redimensionner
//}
//
//void Dungeon::AfficherDimensionsConsole() {
//    // R�cup�rer le handle de la console
//    HWND console = GetConsoleWindow();
//
//    // R�cup�rer les dimensions actuelles de la fen�tre de console
//    RECT r;
//    GetWindowRect(console, &r);
//
//    // Calculer la largeur et la hauteur
//    int largeur = r.right - r.left;
//    int hauteur = r.bottom - r.top;
//
//    // Afficher les dimensions
//    std::cout << "Dimensions actuelles de la fen�tre : " << largeur << "x" << hauteur << std::endl;
//}