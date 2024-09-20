#include "Dungeon.h"
#include <string>
#include <iomanip>
#include "Fighter.h"
#include "Hero.h"
#include "Golem.h"
#include "Spectre.h"
#include "Mower.h"
#include "Message.h"
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
    m_message(nullptr),
    m_heroPtr(nullptr),
    m_widthWithOffsetDungeon(0),
    m_heightWithOffsetDungeon(0),
    m_widthDungeon(0),
    m_heightDungeon(0),
    m_currentTurn(1),
    m_dungeonRoom(1)
{

}

Dungeon::Dungeon(int width, int height) :
    m_heroPtr(nullptr),
    m_widthDungeon(width),
    m_heightDungeon(height),
    m_widthWithOffsetDungeon(0),
    m_heightWithOffsetDungeon(0),
    m_currentTurn(1),
    m_dungeonRoom(1)
{
    m_message = new Message(this);
    m_fightersPtr = std::vector<Fighter*>();

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
                    entityData.Position, 6, 4, 2, 3,m_heroPtr);
            break;
        case EntityType::Spectre:
            mob =
                new Spectre(entityData.Position, 3, 1, 2, 3, m_heroPtr);
            break;
        case EntityType::Golem:
            mob =
                new Golem(entityData.Position, 12, 2, 1, 3, m_heroPtr);
            break;
        default:
            break;
        }
        if (mob != nullptr)
        {
            AddFighter(mob);
        }
    }


    for (Fighter* fighter : m_fightersPtr)
    {
        UpdateMovePossibility(fighter);
    }
}

void Dungeon::Clear()
{
    for (Fighter* fighter : m_fightersPtr)
    {
        delete fighter;
    }

    m_fightersPtr.clear();
}

void Dungeon::AddFighter(Fighter* fighter)
{
    m_fightersPtr.push_back(fighter);
}

void Dungeon::RemoveFighters()
{
    for (auto it = m_fightersPtr.begin(); it != m_fightersPtr.end();)
    {
        
        if ((*it)->m_isDead)
        {
            if (dynamic_cast<Hero*>((*it)))
            {
                m_heroPtr = nullptr;
            }
            delete* it;
            it = m_fightersPtr.erase(it);
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
    m_heroPtr = player;
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

            for (Fighter* entity : m_fightersPtr)
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

    for (Fighter* fighter : m_fightersPtr)
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
        Golem* golem = new Golem(randomPos, maxLife * 2, attackDamage, sizeCanMove, 3, m_heroPtr);
        return golem;
    }

    case (int)EnumMob::Spectre: {
        Spectre* spectre = new Spectre(randomPos, maxLife / 2, attackDamage / 2, sizeCanMove * 2, 3, m_heroPtr);
        return spectre;
    }

    case (int)EnumMob::Mower: {
        Mower* mower = new Mower(randomPos, 10, attackDamage * 2, sizeCanMove * 2, 3, m_heroPtr);
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
    fighter->SetRemoveFighterPosPossibility(&m_fightersPtr);
}

void Dungeon::UpdateNearFighterPlayer()
{
    if (m_heroPtr == nullptr)
    {
        return;
    }
    m_heroPtr->SetNearPosPlayer(m_fightersPtr);
}

void Dungeon::HandleOnAttackAllFighters(Fighter* origin)
{
    for (Fighter* fighter : m_fightersPtr) 
    {
        if (!dynamic_cast<Hero*>(fighter))
        {
            origin->Attack(fighter);
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
    InitTabChar();
    ReplaceEntity();

    m_message->Draw();
}

void Dungeon::InitTabChar()
{
    m_tabCharGame = std::vector<std::vector<char>>();

    if (m_heightDungeon % 2 != 0) {
        m_heightDungeon++;
    }
    if (m_widthDungeon % 2 != 0) {
        m_widthDungeon++;
    }

    m_widthWithOffsetDungeon = m_widthDungeon * DRAW_OFFSET + 1;
    m_heightWithOffsetDungeon = m_heightDungeon * DRAW_OFFSET + 1;

    m_tabCharGame.resize(m_heightDungeon, std::vector<char>(m_widthDungeon, (' ')));
}

void Dungeon::ReplaceEntity()
{
    for (Fighter* fighter : m_fightersPtr)
    {
        for (Maths::Vector2 posPossible : fighter->GetMovePosPossibility())
        {
            if (!fighter->isHisTurn) 
            {
                continue;
            }

            m_tabCharGame[posPossible.m_y][posPossible.m_x] = 'm';

            if (fighter == m_heroPtr) {
                m_tabCharGame[posPossible.m_y][posPossible.m_x] = 'a';
            }
        }
    }

    for (Fighter* fighter : m_fightersPtr)
    {
        Maths::Vector2 vect = fighter->GetPosition();
        m_tabCharGame[vect.m_y][vect.m_x] = fighter->GetSprite();
    }
}

std::vector<std::string>* Dungeon::GetDungeonString()
{
    std::vector<std::string>* tabCharGame = new std::vector<std::string>();
    tabCharGame->resize(m_heightWithOffsetDungeon, "");

    for (int i = 0; i < m_heightWithOffsetDungeon; i++)
    {
        for (int j = 0; j < m_widthWithOffsetDungeon; j++)
        {
            if (i % DRAW_OFFSET == 0 || j % DRAW_OFFSET == 0)
            {
                (*tabCharGame)[i] += FillBoundsOrDefaultChar(j % DRAW_OFFSET == 0, i % DRAW_OFFSET == 0);
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

                (*tabCharGame)[i] += txt;
            }

            else 
            {
                (*tabCharGame)[i] += ' ';
            }
            
        }
    }
    return tabCharGame;
}
