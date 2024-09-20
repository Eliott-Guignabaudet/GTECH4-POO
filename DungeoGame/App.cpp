#include <iostream>

#include "App.h"
#include "Time.h"
#include "Dungeon.h"
#include "DungeonParser.h"
#include "Message.h"
#include "Input.h"
#include <iomanip>

#include "PlayerController.h"
#include "IAController.h"

#pragma region Fighters Includes

#include "Fighter.h"
#include "Hero.h"
#include "Mower.h"
#include "Golem.h"
#include "Spectre.h"

#pragma endregion

#pragma region IABrain Includes

#include "IAMowerBrain.h"
#include "IASpectreBrain.h"
#include "IAGolemBrain.h"

#pragma endregion

#pragma region StateMachine Includes

#include "StateMachine.h"
#include "InitState.h"
#include "PlayerTurnState.h"
#include "IATurnState.h"
#include "GameOverState.h"

#pragma endregion

#if _DEBUG
const int MAX_ROOM = 1;
#else
const int MAX_ROOM = 10;
#endif
using namespace std::placeholders;

#pragma region Singleton
App* App::s_instance = nullptr;

App::App() :
	m_gameStateMachine(nullptr),
	m_dungeon(nullptr),
	m_playerController(nullptr)
{

}

App* App::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new App();
	}
    return s_instance;
}
#pragma endregion

void App::Run()
{
	std::cout << "Start Application" << std::endl;
	Time::GetInstance()->StartTime();
	Init();
	RegisterForEvents();
	Draw();
	while (!m_isGameFinish)
	{
		if (Time::GetInstance()->UpdateTime())
		{
			Input::UpdateKeyStates();
			Update(); 
		}
	}
	Sleep(1000);
	system("cls");
	std::cout << "Congratulation! You Win!" << std::endl;
}

#pragma region Lifecycle

void App::Init()
{
	int width = 20;
	int height = 10;
	m_dungeon = new Dungeon(width, height);


	m_gameStateMachine = new StateMachine();
	InitDungeon(width, height);
	InitControllers();
	InitStateMachine();

}

void App::InitStateMachine()
{
	InitState* initState = new InitState();
	PlayerTurnState* playerTurnState = new PlayerTurnState();
	IATurnState* iaTurnState = new IATurnState();
	GameOverState* gameOverState = new GameOverState();

	std::vector<State*> states =
	{
		initState,
		playerTurnState,
		iaTurnState,
		gameOverState
	};
	

	m_gameStateMachine->Init(states);

	m_gameStateMachine->SwitchToState(playerTurnState);
}

void App::InitDungeon(int width, int height)
{
#if _DEBUG
	m_dungeon->InitWithData(DungeonParser::ParseDungeon("DungeonMap.txt"));
#else
	m_dungeon->SpawnPlayer(width / 2, height / 2);
	m_dungeon->SpawnMob();
#endif
}

void App::InitControllers()
{
	if (m_playerController == nullptr)
	{
		m_playerController = new PlayerController();
	}
	m_playerController->PossessFighter(m_dungeon->m_heroPtr);

	std::vector<Fighter*> fighters = m_dungeon->m_fightersPtr;
	for (int i = 0; i < fighters.size(); i++)
	{
		Fighter* currentFighter = fighters[i];
		if (dynamic_cast<Hero*>(fighters[i]))
		{
			continue;
		}
		if (IAController* newIAController = 
			TryCreateIAController<Mower, IAMowerBrain>(currentFighter))
		{
			m_iasControllers.push_back(newIAController);
		}
		else if (IAController* newIAController =
			TryCreateIAController<Golem, IAGolemBrain>(currentFighter))
		{
			m_iasControllers.push_back(newIAController);
		}
		else if (IAController* newIAController =
			TryCreateIAController<Spectre, IASpectreBrain>(currentFighter))
		{
			m_iasControllers.push_back(newIAController);
		}
	}
}

void App::RegisterForEvents()
{
	auto onPlayerFinishTurnBind =
		std::bind( &App::HandleOnPlayerFinishTurn, this);
	m_playerController->OnFinishTurn = onPlayerFinishTurnBind;
	auto onRedrawFighterBind =
		std::bind(&App::HandleOnRedrawFighter, this, _1);
	Fighter::OnRedrawMoveFighter = onRedrawFighterBind;

	auto onFighterSendActionMessageBind =
		std::bind(&App::HandleOnFighterSendMessage, this, _1);
	Fighter::OnFighterSendActionMessage = onFighterSendActionMessageBind;

	IATurnState* iaTurnState =
		m_gameStateMachine->GetState<IATurnState>();
	auto onIaTurnFinishBind =
		std::bind(&App::HandleOnFinishIATurn, this);
	auto onIAControllerFinishBind =
		std::bind(&App::HandleOnIAControllerFinish, this);
	
	iaTurnState->OnFinishIATurn = onIaTurnFinishBind;
	iaTurnState->OnIAControllerFinish = onIAControllerFinishBind;

}

void App::Update()
{
	m_playerController->Update();
	m_gameStateMachine->Update();
}

void App::UpdateAllFighterPossibilities()
{
	m_dungeon->RemoveFighters();
	std::vector<Fighter*> fighters = m_dungeon->m_fightersPtr;
	for (int i = 0; i < fighters.size(); i++)
	{
		m_dungeon->UpdateMovePossibility(fighters[i]);
	}
}

void App::Draw()
{
	system("cls");
	State* state = m_gameStateMachine->GetCurrentState();
	std::cout << std::setw(25) << std::right << std::setw(25) << " Room : " + std::to_string(m_dungeon->m_dungeonRoom) ;
	std::cout << std::setw(25) << std::right << std::setw(25) << " Turn : " + std::to_string(m_dungeon->m_currentTurn) << std::setw(25) << std::right;
	if (dynamic_cast<PlayerTurnState*>(state))
	{
		std::string playerTurnStateTxt = "Player Turn\n";
		std::cout << TXT_BLUE + playerTurnStateTxt + TXT_RESET;
	}
	if (dynamic_cast<IATurnState*>(state))
	{
		std::string iaTurnStateTxt = "IA Turn\n";
		std::cout << TXT_RED + iaTurnStateTxt + TXT_RESET;
	}

	m_dungeon->Draw();
#if _DEBUG
	std::cout 
		<< Time::GetInstance()->GetElapsedTime() 
		<< std::endl;
#endif
}

void App::RemoveIAController(IAController* iaController)
{
	int iaIndex = 0;
	for (int i = 0; i < m_iasControllers.size() && m_iasControllers[iaIndex] != iaController; i++)
	{
		iaIndex = i;
	}
	m_iasControllers.erase(m_iasControllers.begin() + iaIndex);
	delete iaController;
	if (m_iasControllers.size() == 0)
	{
		if (m_dungeon->m_dungeonRoom >= MAX_ROOM)
		{
			m_isGameFinish = true;
		}
		m_dungeon->m_currentTurn = 1;
		m_dungeon->m_dungeonRoom++;
		m_dungeon->SpawnMob();
		InitControllers();
	}
}

#pragma endregion

#pragma region Events

void App::HandleOnPlayerFinishTurn()
{
	m_dungeon->m_heroPtr->isHisTurn = false;
	State* iaTurnState =
		m_gameStateMachine->GetState<IATurnState>();
	m_gameStateMachine->SwitchToState(iaTurnState);
	UpdateAllFighterPossibilities();
	m_dungeon->UpdateNearFighterPlayer();
	Draw();
	Sleep(1000);
	m_dungeon->m_message->ClearStockMessage();
}

void App::HandleOnFinishIATurn()
{
	m_dungeon->m_currentTurn++;
	State* playerTurnState =
		m_gameStateMachine->GetState<PlayerTurnState>();
	m_gameStateMachine->SwitchToState(playerTurnState);
	if (m_dungeon->m_heroPtr == nullptr || m_dungeon->m_heroPtr->m_isDead)
	{
		ResetDungeon();
	}
	UpdateAllFighterPossibilities();
	m_dungeon->UpdateNearFighterPlayer();
	Draw();
	
}

void App::HandleOnIAControllerFinish()
{
	UpdateAllFighterPossibilities();
}

void App::HandleOnRedrawFighter(Fighter* fighter)
{
	m_dungeon->UpdateNearFighterPlayer();
	Draw();
}

void App::HandleOnFighterSendMessage(std::string message)
{
	m_dungeon->m_message->AddMessage(message);
}
#pragma endregion

void App::ResetDungeon()
{
	m_dungeon->m_message->ClearStockMessage();
	m_dungeon->Clear();
	m_dungeon->m_heroPtr = nullptr;
	for (int i = 0; i < m_iasControllers.size(); i++)
	{
		if (m_iasControllers[i] == nullptr)
		{
			continue;
		}
		if (m_iasControllers[i]->GetIABrain() != nullptr)
		{
			delete m_iasControllers[i]->GetIABrain();
		}
		delete m_iasControllers[i];
	}
	m_iasControllers.clear();
	InitDungeon(20, 10);
	InitControllers();
	m_dungeon->m_dungeonRoom = 1;
	m_dungeon->m_currentTurn = 1;
}


#pragma region Getters

PlayerController* App::GetPlayerController()
{
	return m_playerController;
}

std::vector<IAController*> App::GetIasControllers()
{
	return m_iasControllers;
}

#pragma endregion