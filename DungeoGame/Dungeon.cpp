#include "Dungeon.h"
#include <string>
#include <iomanip>
#include "Fighter.h"
#include "Hero.h"
#include "Golem.h"
#include "Spectre.h"
#include "Mower.h"
#include "DungeonParser.h"

const char CORNER_WALL = '*';
const char HORIZONTAL_WALL = '-';
const char VERTICAL_WALL = '|';
const int DRAW_OFFSET = 2;

using namespace std::placeholders;

enum class EnumMob {
    Golem = 0,
    Spectre,
    Mower,
    Size
};


Dungeon::Dungeon() :
    m_csbi(nullptr),
    m_heroEntity(nullptr),
    m_maxWidthDungeon(0),
    m_widthDungeon(0),
    m_heightDungeon(0)
{

}

Dungeon::Dungeon(int width, int height) :
    m_heroEntity(nullptr),
    m_widthDungeon(width),
    m_heightDungeon(height)
{
    m_csbi = new CONSOLE_SCREEN_BUFFER_INFO();
    m_maxWidthDungeon = GetConsoleWidthSize();
    m_fighters = std::vector<Fighter*>();

    auto onAttackAllFighter =
        std::bind(&Dungeon::HandleOnAttackAllFighters, this, _1);
    Mower::OnAttackAllFighter = onAttackAllFighter;

    //std::srand(time(NULL));
}

void Dungeon::InitWithData(const DungeonData& data)
{
    m_widthDungeon = data.Width;
    m_heightDungeon = data.Height;
    for (int i = 0; i < data.Entities.size(); i++)
    {
        EntityData entityData = data.Entities[i];
        switch (entityData.Type)
        {
        case EntityType::Hero:
            SpawnPlayer(entityData.Position.m_x, entityData.Position.m_y);
        }
    }
    for (int i = 0; i < data.Entities.size(); i++)
    {
        EntityData entityData = data.Entities[i];
        Mob* mob = nullptr;
        switch (entityData.Type)
        {
        case EntityType::Mower:
            mob =
                new Mower(
                    entityData.Position, 6, 4, 2, 3,m_heroEntity);
            break;
        case EntityType::Spectre:
            mob =
                new Spectre(entityData.Position, 3, 1, 2, 3, m_heroEntity);
            break;
        case EntityType::Golem:
            mob =
                new Golem(entityData.Position, 12, 2, 1, 3, m_heroEntity);
            break;
        default:
            break;
        }
        if (mob != nullptr)
        {
            AddFighter(mob);
        }
    }


    for (Fighter* fighter : m_fighters)
    {
        UpdateMovePossibility(fighter);
    }
}

void Dungeon::Clear()
{
    for (Fighter* fighter : m_fighters)
    {
        delete fighter;
    }

    m_fighters.clear();
}

void Dungeon::AddFighter(Fighter* fighter)
{
    m_fighters.push_back(fighter);
}

void Dungeon::RemoveFighters()
{
    for (auto it = m_fighters.begin(); it != m_fighters.end();)
    {
        if ((*it)->m_isDead)
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
    Maths::Vector2 posPlayer = Maths::Vector2(x, y);
    int maxLife = 10;
    int attackDamage = 10;
    int sizeCanMove = 4;

    Hero* player = new Hero(posPlayer, maxLife, attackDamage, sizeCanMove);
    m_heroEntity = player;
    AddFighter(player);
}

void Dungeon::SpawnMob(int nbMob)
{
    for (int i = 0; i < nbMob; i++)
    {
        bool isOk = false;
        Maths::Vector2 pos = Maths::Vector2(0,0);

        while (!isOk) 
        {
            pos.m_x = (std::rand() % m_widthDungeon);
            pos.m_y = (std::rand() % m_heightDungeon);
            isOk = true;

            for (Fighter* entity : m_fighters)
            {
                if (entity->GetPosition() == pos)
                {
                    isOk = false;
                }
            }
        }

        Mob* mob = GetRandomMob(pos);
        if (mob != nullptr) 
        {
            AddFighter(mob);
        }
    }

    for (Fighter* fighter : m_fighters)
    {
        UpdateMovePossibility(fighter);
    }
}

Mob* Dungeon::GetRandomMob(Maths::Vector2 randomPos)
{
    int id = std::rand() % (int)EnumMob::Size;

    int maxLife = 6;
    int attackDamage = 2;
    int sizeCanMove = 1;

    switch (id) {

    case (int)EnumMob::Golem: {
        Golem* golem = new Golem(randomPos, maxLife * 2, attackDamage, sizeCanMove, 3, m_heroEntity);
        return golem;
    }

    case (int)EnumMob::Spectre: {
        Spectre* spectre = new Spectre(randomPos, maxLife / 2, attackDamage / 2, sizeCanMove * 2, 3, m_heroEntity);
        return spectre;
    }

    case (int)EnumMob::Mower: {
        Mower* mower = new Mower(randomPos, 10, attackDamage * 2, sizeCanMove * 2, 3, m_heroEntity);
        return mower;
    }

    default: {
        return nullptr;
    }

    }
}

void Dungeon::UpdateMovePossibility(Fighter* fighter)
{
    fighter->SetMovePosPossibility(m_widthDungeon, m_heightDungeon);
    fighter->SetRemoveFighterPosPossibility(&m_fighters);
}

void Dungeon::UpdateNearFighterPlayer()
{
    m_heroEntity->SetNearPosPlayer(m_fighters);
}

int Dungeon::GetConsoleWidthSize()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hStdOut, m_csbi)) {
        int width = m_csbi->srWindow.Right - m_csbi->srWindow.Left + 1;
        return width;
    }
}

void Dungeon::HandleOnAttackAllFighters(Fighter* origin)
{
    for (Fighter* fighter : m_fighters) 
    {
        if (!dynamic_cast<Hero*>(fighter))
        {
            origin->Attack(fighter);
        }
    }
    //RemoveFighters();
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
    m_maxWidthDungeon = GetConsoleWidthSize();

    InitTabChar();
    ReplaceEntity();
    DrawTabChar();
    DrawStatistics();
}

void Dungeon::InitTabChar()
{
    m_tabChar = std::vector<std::vector<char>>();
    m_tabChar.resize(m_heightDungeon + 1, std::vector<char>(m_widthDungeon + 1, (' ')));

    //for (int i = 0; i <= m_heightDungeon; i++)
    //{
    //    bool yIsInLimit = (i == 0 || i == m_heightDungeon);

    //    for (int j = 0; j <= m_widthDungeon; j++)
    //    {
    //        bool xIsInLimit = (j == 0 || j == m_widthDungeon);


    //        tabChar[i][j] = FillBoundsOrDefaultChar(xIsInLimit, yIsInLimit);
    //    }
    //}
}

void Dungeon::ReplaceEntity()
{
    for (Fighter* fighter : m_fighters)
    {
        for (Maths::Vector2 posPossible : fighter->GetMovePosPossibility())
        {
            if (!fighter->isHisTurn) 
            {
                continue;
            }

            m_tabChar[posPossible.m_y][posPossible.m_x] = 'm';

            if (fighter == m_heroEntity) {
                m_tabChar[posPossible.m_y][posPossible.m_x] = 'a';
            }
        }
    }

    for (Fighter* fighter : m_fighters)
    {
        Maths::Vector2 vect = fighter->GetPosition();
        m_tabChar[vect.m_y][vect.m_x] = fighter->GetSprite();
    }
}

void Dungeon::DrawTabChar()
{
    for (int i = 0; i <= (m_heightDungeon * DRAW_OFFSET); i++)
    {
        DrawOffsetRight();

        for (int j = 0; j <= (m_widthDungeon * DRAW_OFFSET); j++)
        {
            if (i % DRAW_OFFSET == 0 || j % DRAW_OFFSET == 0)
            {
                std::cout << FillBoundsOrDefaultChar(j % DRAW_OFFSET == 0, i % DRAW_OFFSET == 0);
                continue;
            }
            else if (i % DRAW_OFFSET == (DRAW_OFFSET / 2) && j % DRAW_OFFSET == (DRAW_OFFSET / 2))
            {
                char currentChar = m_tabChar[i / DRAW_OFFSET][j / DRAW_OFFSET];
                std::string prefix = "";
                std::string suffix = "\033[0m";

                if (currentChar == 'G' || currentChar == 'S' || currentChar == 'F')  // Mob
                {
                    prefix = "\033[40;31m"; // Fond Noir (40), Texte Rouge (31)
                }

                else if (currentChar == 'm') // Possibility Mob move
                {
                    currentChar = ' ';
                    prefix = "\033[41m"; // Fond Rouge (41), Texte par défaut (blanc)
                }

                else if (currentChar == '@') // Player
                {
                    prefix = "\033[40;36m"; // Fond Noir (40), Texte Cyan (36)
                }

                else if (currentChar == 'a') // Possibility Player move
                {
                    currentChar = ' ';
                    prefix = "\033[42m"; // Fond Vert (42), Texte par défaut (blanc)
                }

                std::string txt = prefix + currentChar + suffix;

                std::cout << txt;
            }
            else 
            {
                std::cout << ' ';
            }
            
        }
        std::cout << '\n';
    }
}

void Dungeon::DrawStatistics()
{
    DrawLineWithAnything('-');

    DrawLineTitle('*', "Player Statistics :");

    DrawLineWithNothing('*');

    DrawLineElement('*', "Life :", std::to_string(m_heroEntity->GetLife()));
    DrawLineElement('*', "Attack :", std::to_string(m_heroEntity->GetAttackDamage()));

    DrawLineWithAnything('-');
}

void Dungeon::DrawOffset(int offset)
{
    if (offset == 0) {
        offset = (m_maxWidthDungeon - (m_widthDungeon * DRAW_OFFSET)) / 2;
    }
    std::cout << std::setw(offset - 1);
}

void Dungeon::DrawOffsetRight(int offset)
{
    DrawOffset(offset);
    std::cout << std::right << ' ';
}

void Dungeon::DrawOffsetLeft(int offset)
{
    DrawOffset(offset + 1);
    std::cout << std::left;
}

void Dungeon::DrawLineTitle(char Char, std::string message)
{
    DrawOffsetRight();
    int marge = (m_widthDungeon * DRAW_OFFSET) / 10;

    std::cout << Char;
    DrawOffsetRight(marge);
    DrawOffsetLeft((m_widthDungeon * DRAW_OFFSET) - marge);
    std::cout << message << Char;

    std::cout << "\n";
}

void Dungeon::DrawLineElement(char Char, std::string message1, std::string message2)
{
    DrawOffsetRight();
    int marge = (m_widthDungeon * DRAW_OFFSET) / 5;

    std::cout << Char;
    DrawOffsetRight(marge);
    DrawOffsetLeft(marge * 2);
    std::cout << message1;
    DrawOffsetLeft(marge * 2);
    std::cout << message2 << Char;
    std::cout << "\n";
}

void Dungeon::DrawLineWithNothing(char Char) 
{
    DrawOffsetRight();

    std::cout << Char;
    DrawOffsetRight(m_widthDungeon * DRAW_OFFSET);
    std::cout << Char;

    std::cout << "\n";
}

void Dungeon::DrawLineWithAnything(char Char) 
{
    DrawOffsetRight();

    for (int i = 0; i <= m_widthDungeon * DRAW_OFFSET; i++)
    {
        std::cout << Char;
    }

    std::cout << "\n";
}
