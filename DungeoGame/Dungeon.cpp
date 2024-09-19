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
    m_heightDungeon(0),
    m_dungeonRoom(1)
{

}

Dungeon::Dungeon(int width, int height) :
    m_heroEntity(nullptr),
    m_widthDungeon(width),
    m_heightDungeon(height),
    m_dungeonRoom(1)
{
    m_csbi = new CONSOLE_SCREEN_BUFFER_INFO();
    m_maxWidthDungeon = GetConsoleWidthSize();
    m_fighters = std::vector<Fighter*>();

    auto onAttackAllFighter =
        std::bind(&Dungeon::HandleOnAttackAllFighters, this, _1);
    Mower::OnAttackAllFighter = onAttackAllFighter;

    std::srand(time(NULL));
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

    //m_tabStringStatistics = std::vector<std::string>>();
    m_tabStringStatistics.resize(m_heightDungeon + 1);

    InitTabChar();
    InitStatistics();
    ReplaceEntity();
    DrawTabChar();
}

void Dungeon::InitTabChar()
{
    m_tabCharGame = std::vector<std::vector<char>>();
    m_tabCharGame.resize(m_heightDungeon + 1, std::vector<char>(m_widthDungeon + 1, (' ')));
}

void Dungeon::InitStatistics()
{
    m_tabStringStatistics = std::vector<std::string>();
    m_tabStringStatistics.resize((m_heightDungeon * DRAW_OFFSET) + 1, "");

    if (m_tabStringStatistics.size() >= 5) 
    {
        m_tabStringStatistics[0] = DrawLineWithAnything('-');
        m_tabStringStatistics[1] = DrawLineTitle('*', "Player Statistics :");
        m_tabStringStatistics[2] = DrawLineElement('*', "Life :", std::to_string(m_heroEntity->GetLife()));
        m_tabStringStatistics[3] = DrawLineElement('*', "Attack :", std::to_string(m_heroEntity->GetAttackDamage()));
        m_tabStringStatistics[5] = DrawLineTitle('*', "Space:NextTurn");
    }

    int cpt = 1;
    for (Fighter* fighter : m_heroEntity->GetNearFightPlayer()) 
    {
        m_tabStringStatistics[5] = DrawLineElement('*', "Enter:Attack", "Space:NextTurn");
        int nbSize = (5 + (3 * cpt)) + cpt;
        if (m_tabStringStatistics.size() > nbSize)
        {
            m_tabStringStatistics[nbSize - 2] = DrawLineTitle('*', fighter->GetName() + " Statistics :");
            m_tabStringStatistics[nbSize - 1] = DrawLineElement('*', "Life :", std::to_string(fighter->GetLife()));
            m_tabStringStatistics[nbSize] = DrawLineElement('*', "Attack :", std::to_string(fighter->GetAttackDamage()));
        }
        cpt += 1;
    }
    m_tabStringStatistics[m_tabStringStatistics.size() - 1] = DrawLineWithAnything('-');

    for(int i = 0; i < m_tabStringStatistics.size(); i++)
    {
        if (m_tabStringStatistics[i] == "")
        {
            m_tabStringStatistics[i] = DrawLineWithNothing('*');
        }
        
    }
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

            m_tabCharGame[posPossible.m_y][posPossible.m_x] = 'm';

            if (fighter == m_heroEntity) {
                m_tabCharGame[posPossible.m_y][posPossible.m_x] = 'a';
            }
        }
    }

    for (Fighter* fighter : m_fighters)
    {
        Maths::Vector2 vect = fighter->GetPosition();
        m_tabCharGame[vect.m_y][vect.m_x] = fighter->GetSprite();
    }
}

void Dungeon::DrawTabChar()
{
    std::vector<std::string> tabCharGame = std::vector<std::string>();
    tabCharGame.resize((m_heightDungeon * DRAW_OFFSET) + 1, "");

    for (int i = 0; i <= (m_heightDungeon * DRAW_OFFSET); i++)
    {
        for (int j = 0; j <= (m_widthDungeon * DRAW_OFFSET); j++)
        {
            if (i % DRAW_OFFSET == 0 || j % DRAW_OFFSET == 0)
            {
                tabCharGame[i] += FillBoundsOrDefaultChar(j % DRAW_OFFSET == 0, i % DRAW_OFFSET == 0);
                continue;
            }
            else if (i % DRAW_OFFSET == (DRAW_OFFSET / 2) && j % DRAW_OFFSET == (DRAW_OFFSET / 2))
            {
                char currentChar = m_tabCharGame[i / DRAW_OFFSET][j / DRAW_OFFSET];
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

                tabCharGame[i] += txt;
            }
            else 
            {
                tabCharGame[i] += ' ';
            }
            
        }
    }

    int offset = m_maxWidthDungeon - (m_tabStringStatistics[0].size() * DRAW_OFFSET);

    for (int i = 0; i <= m_heightDungeon * DRAW_OFFSET; i++)
    {
        std::string currentString = DrawOffset(offset / (DRAW_OFFSET + 1));
        currentString += m_tabStringStatistics[i];
        currentString += DrawOffset(offset / (DRAW_OFFSET + 1));
        currentString += tabCharGame[i];
        currentString += DrawOffset(offset / (DRAW_OFFSET + 1));
        std::cout << currentString;
        std::cout << "\n";
    }
}

std::string Dungeon::DrawOffset(int offset)
{
    std::string offsetStr = "";
    for (int i = 0; i < offset; i++) 
    {
        offsetStr += ' ';
    }
    return offsetStr;
}

std::string Dungeon::DrawLineTitle(char Char, std::string message)
{
    std::string newString = "";
    int sizeWidth = m_widthDungeon * DRAW_OFFSET;
    int marge = sizeWidth / 10;

    newString += Char;
    newString += DrawOffset(marge - 1);
    newString += message;
    newString += DrawOffset(sizeWidth - newString.size());
    newString += Char;

    return newString;
}

std::string Dungeon::DrawLineElement(char Char, std::string message1, std::string message2)
{
    std::string newString = "";
    int sizeWidth = m_widthDungeon * DRAW_OFFSET;
    int offset = sizeWidth - (message1.size() + message2.size() + 2);
    int marge = offset / 3;

    newString += Char;
    newString += DrawOffset(marge);
    newString += message1;
    newString += DrawOffset(marge);
    newString += message2;
    newString += DrawOffset(marge);
    newString += DrawOffset(sizeWidth - newString.size());
    newString += Char;

    return newString;
}

std::string Dungeon::DrawLineWithNothing(char Char)
{
    std::string newString = "";

    newString += Char;
    newString += DrawOffset(m_widthDungeon * DRAW_OFFSET - 1);
    newString += Char;

    return newString;
}

std::string Dungeon::DrawLineWithAnything(char Char)
{
    std::string newString = "";

    for (int i = 0; i <= m_widthDungeon * DRAW_OFFSET; i++)
    {
        newString += Char;
    }

    return newString;
}
