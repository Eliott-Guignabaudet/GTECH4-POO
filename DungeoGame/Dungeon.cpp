#include "Dungeon.h"
#include <iostream>
#include <Windows.h>
#include "Hero.h"
#include "Golem.h"
#include "Spectre.h"
#include "Mower.h"

const char CORNER_WALL = '*';
const char HORIZONTAL_WALL = '-';
const char VERTICAL_WALL = '|';

enum class EnumMob {
    Golem = 0,
    Spectre,
    Mower,
    Size
};


Dungeon::Dungeon() :
    m_heroEntity(nullptr),
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

    std::srand(time(NULL));

    SpawnPlayer(m_widthDungeon / 2, m_heightDungeon / 2);
    SpawnMob();
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

void Dungeon::SpawnPlayer(int x, int y)
{
    Maths::Vector2* posPlayer = new Maths::Vector2(x, y);
    Hero* player = new Hero(posPlayer, 10, 10, 3);
    m_heroEntity = player;
    AddEntity(player);
}

void Dungeon::SpawnMob(int nbMob)
{
    for (int i = 0; i < nbMob; i++)
    {
        bool isOk = false;
        Maths::Vector2* pos = new Maths::Vector2(0,0);

        while (!isOk) 
        {
            pos->m_x = ((std::rand() % m_widthDungeon - 1) + 1);
            pos->m_y = ((std::rand() % m_heightDungeon - 1) + 1);
            isOk = true;

            for (Entity* entity : m_entities)
            {
                if (*entity->GetPosition() == *pos)
                {
                    isOk = false;
                }
            }
        }

        Mob* mob = GetRandomMob(pos);
        if (mob != nullptr) 
        {
            mob->SetHeroTarget(m_heroEntity);
            AddEntity(mob);
        }
    }
}

Mob* Dungeon::GetRandomMob(Maths::Vector2* randomPos)
{
    int id = std::rand() % (int)EnumMob::Size;

    switch (id) {

    case (int)EnumMob::Golem: {
        Golem* golem = new Golem(randomPos, 10, 3, 3, 3);
        return golem;
    }

    case (int)EnumMob::Spectre: {
        Spectre* spectre = new Spectre(randomPos, 10, 3, 3, 3);
        return spectre;
    }

    case (int)EnumMob::Mower: {
        Mower* mower = new Mower(randomPos, 10, 3, 3, 3);
        return mower;
    }

    default: {
        return nullptr;
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
    for (int i = 0; i <= m_heightDungeon; i++)
    {
        bool yIsInLimit = (i == 0 || i == m_heightDungeon);

        for (int j = 0; j <= m_widthDungeon; j++)
        {
            bool xIsInLimit = (j == 0 || j == m_widthDungeon);

            bool isDrawLimitBounds = DrawLimitBounds(xIsInLimit, yIsInLimit);

            if (!isDrawLimitBounds) 
            {
                bool isDefaultEntity = true;

                for (Entity* entity : m_entities)
                {
                    Maths::Vector2 vect = *entity->GetPosition();
                    if (vect == Maths::Vector2(j, i))
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
//    // Récupérer le handle de la console
//    HWND console = GetConsoleWindow();
//
//    // Définir la nouvelle taille de la fenêtre
//    RECT r;
//    GetWindowRect(console, &r); // Récupérer la position actuelle de la fenêtre
//    MoveWindow(console, r.left, r.top, m_widthDungeon, m_heightDungeon, TRUE); // Redimensionner
//}
//
//void Dungeon::AfficherDimensionsConsole() {
//    // Récupérer le handle de la console
//    HWND console = GetConsoleWindow();
//
//    // Récupérer les dimensions actuelles de la fenêtre de console
//    RECT r;
//    GetWindowRect(console, &r);
//
//    // Calculer la largeur et la hauteur
//    int largeur = r.right - r.left;
//    int hauteur = r.bottom - r.top;
//
//    // Afficher les dimensions
//    std::cout << "Dimensions actuelles de la fenêtre : " << largeur << "x" << hauteur << std::endl;
//}