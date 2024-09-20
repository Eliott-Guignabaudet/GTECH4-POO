#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

#define TXT_RESET   "\033[0m"          // Réinitialise la couleur
#define TXT_RED     "\033[31m"         // Rouge
#define TXT_GREEN   "\033[32m"         // Vert
#define TXT_YELLOW  "\033[33m"         // Jaune
#define TXT_BLUE    "\033[34m"         // Bleu
#define TXT_MAGENTA "\033[35m"         // Magenta
#define TXT_CYAN    "\033[36m"         // Cyan
#define TXT_WHITE   "\033[37m"         // Blanc

#define BG_RED     "\033[41m"       // Fond rouge
#define BG_GREEN   "\033[42m"       // Fond vert
#define BG_YELLOW  "\033[43m"       // Fond jaune
#define BG_BLUE    "\033[44m"       // Fond bleu
#define BG_MAGENTA "\033[45m"       // Fond magenta
#define BG_CYAN    "\033[46m"       // Fond cyan
#define BG_WHITE   "\033[47m"       // Fond blanc

class Dungeon;
class Fighter;

class Message
{
public:

#pragma region Variables

	CONSOLE_SCREEN_BUFFER_INFO* m_csbi; 
	Dungeon* m_currentDungeon;

	std::vector<std::string> m_tabStringStatistics;
	std::vector<std::string> m_tabStringMessage;
	std::vector<std::string> m_stockMessage;

	int m_windowScreenSize;
	int m_tabMessageSize;

	int m_currentIndexMessage;

#pragma endregion

#pragma region Class function
	Message();
	Message(Dungeon* dungeon);

	int GetConsoleWidthSize();

	std::vector<std::string>* InitTab();
	void InitStatistics();
	void InitMessages();

	void ClearStockMessage();
	void AddMessage(std::string message);

	std::string GetEmptyString(int offset = 0);
	std::string GetTitleLineString(std::string message, std::string color = "", char defaultChar = '*');
	std::string GetElementLineString(std::string message1, std::string message2, std::string color1 = "", std::string color2 = "", char defaultChar = '*');
    std::string GetVoidLineString(int sizeString, char defaultChar = '*');
	std::string GetTopLineString(char defaultChar = '*');

	void RefreshTabMessageSize();
	void SetPlayerStatsString();
	void SetMobStatsString();
	void SetFighterStatsString(int nbSize, Fighter* fighter);
	void SetVoidRemainingLine(std::vector<std::string>* tabString);
	void Draw();
	void DrawWindowScreen(std::vector<std::string>* m_tabCharGame);
#pragma endregion
};

