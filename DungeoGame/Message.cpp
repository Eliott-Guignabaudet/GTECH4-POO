#include "Message.h"
#include <string>
#include <iomanip>
#include "Hero.h"
#include "Dungeon.h"
#include "Mob.h"

Message::Message() : 
    m_csbi(nullptr),
    m_player(nullptr),
    m_currentDungeon(nullptr),
    m_windowScreenSize(0),
    m_tabMessageSize(0),
    m_currentIndexMessage(0)
{

}

Message::Message(Dungeon* dungeon) :
    m_player(nullptr),
    m_windowScreenSize(0),
    m_tabMessageSize(0),
    m_currentIndexMessage(1)
{
    m_csbi = new CONSOLE_SCREEN_BUFFER_INFO();
    m_currentDungeon = dungeon;
}

int Message::GetConsoleWidthSize()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hStdOut, m_csbi)) {
        int width = m_csbi->srWindow.Right - m_csbi->srWindow.Left + 1;
        return width;
    }
}

std::vector<std::string>* Message::InitTab()
{
    std::vector<std::string>* m_tabString = new std::vector<std::string>();
    int heightDungeon = m_currentDungeon->m_heightWithOffsetDungeon;

    m_tabString->resize(heightDungeon, "");

    return m_tabString;
}

void Message::InitStatistics()
{
    if (m_player == nullptr) 
    {
        m_player = m_currentDungeon->m_heroPtr;
    }

    m_tabStringStatistics = *InitTab();
    SetPlayerStatsString();
    SetMobStatsString();
    SetVoidRemainingLine(&m_tabStringStatistics);
}

void Message::InitMessages()
{
    m_tabStringMessage = *InitTab();

    m_tabStringMessage[0] = GetTopLineString();
    m_tabStringMessage[m_tabStringMessage.size() - 1] = GetTopLineString();

    for (int i = 1; i < m_stockMessage.size() + 1; i++) 
    {
        if (i >= m_tabStringMessage.size()) 
        {
            break;
        }
        m_tabStringMessage[i] = GetTitleLineString(m_stockMessage[i - 1]);
    }

    SetVoidRemainingLine(&m_tabStringMessage);
}


void Message::ClearStockMessage()
{
    m_stockMessage.clear();
}

void Message::AddMessage(std::string message)
{
    m_stockMessage.push_back(message);
}

void Message::SetPlayerStatsString()
{
    if (m_tabStringStatistics.size() > 4)
    {
        SetFighterStatsString(2, dynamic_cast<Fighter*>(m_player));
        m_tabStringStatistics[3] = GetTitleLineString("Next: Space", TXT_BLUE);
        m_tabStringStatistics[m_tabStringStatistics.size() - 1] = GetTopLineString();
    }
}

void Message::SetMobStatsString()
{
    int cpt = 1;
    int nbSize = 0;
    for (Fighter* fighter : m_player->GetNearFightPlayer())
    {
        std::string attackTxt = "Attack: Enter";
        std::string nextTxt = "Next: Space";
        m_tabStringStatistics[3] = GetElementLineString(attackTxt,nextTxt, TXT_RED, TXT_BLUE);
        nbSize = (3 + (4 * cpt));
        if (m_tabStringStatistics.size() > nbSize)
        {
            SetFighterStatsString(nbSize - 1, fighter);
            Mob* mob = dynamic_cast<Mob*>(fighter);
            m_tabStringStatistics[nbSize] = GetTitleLineString("Capacity : " + mob->GetCapacityTxt(), TXT_MAGENTA);
        }
        else {
            break;
        }
        cpt++;
    }
    //nbSize = 5 + (4 * (cpt -1));
    //if (nbSize + 1 < m_tabStringStatistics.size())
    //{
    //    m_tabStringStatistics[nbSize + 1] = GetTopLineString();
    //}
}

void Message::SetFighterStatsString(int nbSize, Fighter* fighter)
{
    m_tabStringStatistics[nbSize - 2] = GetTopLineString();
    m_tabStringStatistics[nbSize - 1] = GetTitleLineString(fighter->GetName() + " Statistics :", BG_MAGENTA);
    std::string life = "Life: " + std::to_string(fighter->GetLife());
    std::string attack = "Attack: " + std::to_string(fighter->GetAttackDamage());
    m_tabStringStatistics[nbSize] = GetElementLineString(life,attack, TXT_GREEN, TXT_YELLOW);
}

void Message::SetVoidRemainingLine(std::vector<std::string>* tabString)
{
    int size = m_currentDungeon->m_heightWithOffsetDungeon;
    for (int i = 0; i < size; i++)
    {
        if ((*tabString)[i] == "")
        {
            (*tabString)[i] = GetVoidLineString(m_tabMessageSize + 1);
        }
    }
}

std::string Message::GetEmptyString(int size)
{
    std::string offsetStr = "";
    for (int i = 0; i < size; i++)
    {
        offsetStr += " ";
    }
    return offsetStr;
}

std::string Message::GetTitleLineString(std::string message, std::string color, char defaultChar)
{
    std::string newString = "";
    std::string resetString = TXT_RESET;

    int remainingSpace = m_tabMessageSize - (message.size());
    int newTabMessageSize = (m_tabMessageSize + color.size() + resetString.size());

    newString += defaultChar;
    newString += GetEmptyString(remainingSpace / 2);
    newString += color + message + resetString;
    newString += GetEmptyString(newTabMessageSize - newString.size());
    newString += defaultChar;

    return newString;
}

std::string Message::GetElementLineString(std::string message1, std::string message2, std::string color1, std::string color2, char defaultChar)
{
    std::string newString = "";
    std::string resetString = TXT_RESET;

    int sizeCharMessage = message1.size() + message2.size();
    int sizeCharColor = color1.size() + color2.size();

    int remainingSpace = (m_tabMessageSize - 2) - sizeCharMessage;
    int newTabMessageSize = (m_tabMessageSize + sizeCharColor + (resetString.size() * 2));

    newString += defaultChar;
    newString += GetEmptyString(remainingSpace / 3);
    newString += color1 + message1 + resetString;
    newString += GetEmptyString(remainingSpace / 3);
    newString += color2 + message2 + resetString;
    newString += GetEmptyString(remainingSpace / 3);
    newString += GetEmptyString(newTabMessageSize - newString.size());
    newString += defaultChar;

    return newString;
}

std::string Message::GetVoidLineString(int sizeString, char defaultChar)
{
    std::string newString = "";

    newString += defaultChar;
    newString += GetEmptyString(sizeString - 2);
    newString += defaultChar;

    return newString;
}

std::string Message::GetTopLineString(char defaultChar)
{
    std::string newString = "";

    newString += '*';

    for (int i = 1; i <= m_tabMessageSize - 1; i++)
    {
        newString += defaultChar;
    }

    newString += '*';

    return newString;
}

void Message::RefreshTabMessageSize()
{
    m_windowScreenSize = GetConsoleWidthSize();
    m_tabMessageSize = (m_windowScreenSize - (m_currentDungeon->m_widthWithOffsetDungeon + 8)) / 2;
}

void Message::Draw()
{
    RefreshTabMessageSize();
    InitStatistics();
    InitMessages();
    DrawWindowScreen(m_currentDungeon->GetDungeonString());
}

void Message::DrawWindowScreen(std::vector<std::string>* m_tabCharGame)
{
    int offset = (m_windowScreenSize - (m_tabMessageSize * 2 + (*m_tabCharGame)[0].size())) / 4;

    for (int i = 0; i < m_tabCharGame->size(); i++) 
    {
        std::cout << std::setw(offset) << std::left << ' ';
        std::cout << m_tabStringStatistics[i];

        std::cout << std::setw(offset) << std::left << ' ';
        std::cout << (*m_tabCharGame)[i];

        std::cout << std::setw(offset) << std::left << ' ';
        std::cout << m_tabStringMessage[i];

        std::cout << "\n";
    }
}
