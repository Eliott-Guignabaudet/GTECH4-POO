#include "Dungeon.h"
#include <string>
#include <iomanip>
#include <Windows.h>
#include "Fighter.h"
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
    m_widthDungeon(0),
    m_heightDungeon(0)
{

}

Dungeon::Dungeon(int width, int height) :
    m_widthDungeon(width),
    m_heightDungeon(height)
{
    m_fighters = std::vector<Fighter*>();

    std::srand(time(NULL));

    SpawnPlayer(m_widthDungeon / 2, m_heightDungeon / 2);
    SpawnMob();
}

void Dungeon::Clear()
{
    for (Fighter* fighter : m_fighters)
    {
        delete fighter;
    }

    m_fighters.clear();
}

void Dungeon::AddEntity(Fighter* fighter)
{
    m_fighters.push_back(fighter);
    fighter->UpdateMovePossibility(m_widthDungeon, m_heightDungeon);
}

void Dungeon::RemoveEntity(Fighter* entity)
{
    for (auto it = m_fighters.begin(); it != m_fighters.end();)
    {
        if (*it == entity)
        {
            delete* it;
            it = m_fighters.erase(it);
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
            pos->m_x = (std::rand() % (m_widthDungeon - 1)) + 1;
            pos->m_y = (std::rand() % (m_heightDungeon - 1)) + 1;
            isOk = true;

            for (Entity* entity : m_fighters)
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
        Golem* golem = new Golem(randomPos, 10, 3, 1, 3);
        return golem;
    }

    case (int)EnumMob::Spectre: {
        Spectre* spectre = new Spectre(randomPos, 10, 3, 1, 3);
        return spectre;
    }

    case (int)EnumMob::Mower: {
        Mower* mower = new Mower(randomPos, 10, 3, 1, 3);
        return mower;
    }

    default: {
        return nullptr;
    }

    }
}

char Dungeon::FillBoundsOrDefaultChar(bool xlimit, bool ylimit) 
{
    if (xlimit && ylimit)
    {
        return CORNER_WALL;
    }
    else if (ylimit)
    {
        return HORIZONTAL_WALL;
    }
    else if (xlimit)
    {
        return VERTICAL_WALL;
    }
    else 
    {
        return ' ';
    }
}

void Dungeon::Draw()
{
    //Init Tab Char
    std::vector<std::vector<char>> tabChar = std::vector<std::vector<char>>();
    InitTabChar(&tabChar);

    // Replace Char by Entity
    ReplaceEntity(&tabChar);

    //Draw
    DrawTabChar(&tabChar);

    DrawStatistics();
}

void Dungeon::InitTabChar(std::vector<std::vector<char>>* tabChar)
{
    tabChar->resize(m_heightDungeon + 1, std::vector<char>(m_widthDungeon + 2));

    for (int i = 0; i <= m_heightDungeon; i++)
    {
        bool yIsInLimit = (i == 0 || i == m_heightDungeon);

        for (int j = 0; j <= m_widthDungeon; j++)
        {
            bool xIsInLimit = (j == 0 || j == m_widthDungeon);

            (*tabChar)[i][j] = FillBoundsOrDefaultChar(xIsInLimit, yIsInLimit);
        }
        (*tabChar)[i][m_widthDungeon + 1] = '\n';
    }
}

void Dungeon::ReplaceEntity(std::vector<std::vector<char>>* tabChar)
{
    for (Fighter* fighter : m_fighters)
    {
        for (Maths::Vector2 posPossible : fighter->GetMovePosPossibility())
        {
            (*tabChar)[posPossible.m_y][posPossible.m_x] = 'm';

            if (fighter == m_heroEntity) {
                (*tabChar)[posPossible.m_y][posPossible.m_x] = 'a';
            }
        }

        Maths::Vector2 vect = *fighter->GetPosition();
        (*tabChar)[vect.m_y][vect.m_x] = fighter->GetSprite();
    }
}

void Dungeon::DrawTabChar(std::vector<std::vector<char>>* tabChar)
{
    for (std::vector<char> tabXChar : *tabChar)
    {
        for (char Ychar : tabXChar)
        {
            std::string prefix = "";
            std::string suffix = "\033[0m";

            if (Ychar == 'G' || Ychar == 'S' || Ychar == 'F')  // Mob
            {
                prefix = "\033[41;37m"; // Fond Rouge (41), Text Blanc (37)
            }

            else if (Ychar == 'm') // Possibility Mob move
            {
                Ychar = ' ';
                prefix = "\033[41m"; // Fond Rouge (41)
            }

            else if (Ychar == '@') // Player
            {
                prefix = "\033[42;30m"; // Fond Vert (42), Text Noir (30)
            }

            else if (Ychar == 'a')// Possibility Player move
            {
                Ychar = ' ';
                prefix = "\033[42m"; // Fond Vert (42)
            }

            std::string txt = prefix + Ychar + suffix;

            std::cout << txt;
        }
    }
}

void Dungeon::DrawStatistics()
{
    std::cout << "\n\n";

    DrawLineWithAnything(m_widthDungeon, '-');
    DrawLineWithNothing(m_widthDungeon, '*');

    DrawLineTitle(m_widthDungeon, '*', "Player Statistics :");

    DrawLineWithNothing(m_widthDungeon, '*');

    DrawLineElement(m_widthDungeon, '*', "Life :", std::to_string(m_heroEntity->GetLife()));
    DrawLineElement(m_widthDungeon, '*', "Attack :", std::to_string(m_heroEntity->GetAttackDamage()));

    DrawLineWithNothing(m_widthDungeon, '*');
    DrawLineWithAnything(m_widthDungeon, '-');
}

void Dungeon::DrawLineTitle(int size, char Char, std::string message)
{
    std::cout << std::setw(5) << std::left << Char
        << std::setw(size - 5) << std::left << message
        << Char << "\n";
}

void Dungeon::DrawLineElement(int size, char Char, std::string message1, std::string message2)
{
    std::cout << std::setw((size / 5)) << std::left << Char
        << std::setw((size / 5) * 2) << std::left << message1
        << std::setw((size / 5) * 2) << std::left << message2
        << Char << "\n";
}

void Dungeon::DrawLineWithNothing(int size, char Char) {

    std::cout << std::setw(5) << std::left << Char
        << std::setw(size - 4) << std::right << Char;

    std::cout << "\n";
}

void Dungeon::DrawLineWithAnything(int size, char Char) {

    for (int i = 0; i <= size; i++)
    {
        std::cout << Char;
    }

    std::cout << "\n";
}
