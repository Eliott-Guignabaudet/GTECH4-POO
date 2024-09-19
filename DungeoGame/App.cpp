#include <iostream>

#include "App.h"
#include "Time.h"
#include "Dungeon.h"
#include "DungeonParser.h"
#include "Input.h"

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

#pragma region Singleton

using namespace std::placeholders;

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
	while (true)
	{
		if (Time::GetInstance()->UpdateTime())
		{
			Input::UpdateKeyStates();
			Update(); 
		}
	}
	
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
	//m_dungeon->InitWithData(DungeonParser::ParseDungeon("DungeonMap.txt"));
	m_dungeon->SpawnPlayer(width / 2, height / 2);
	m_dungeon->SpawnMob();
}

void App::InitControllers()
{
	if (m_playerController == nullptr)
	{
		m_playerController = new PlayerController();
	}
	m_playerController->PossessFighter(m_dungeon->m_heroEntity);

	std::vector<Fighter*> fighters = m_dungeon->m_fighters;
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
	std::vector<Fighter*> fighters = m_dungeon->m_fighters;
	for (int i = 0; i < fighters.size(); i++)
	{
		m_dungeon->UpdateMovePossibility(fighters[i]);
	}
}

void App::Draw()
{
	system("cls");

	State* state = m_gameStateMachine->GetCurrentState();
	if (dynamic_cast<PlayerTurnState*>(state))
	{
		std::cout << "Player Turn\n";
	}
	if (dynamic_cast<IATurnState*>(state))
	{
		std::cout << "IA Turn\n";
	}

	m_dungeon->Draw();

	std::cout 
		<< Time::GetInstance()->GetElapsedTime() 
		<< std::endl;
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
		m_dungeon->SpawnMob();
		InitControllers();
	}
}

#pragma endregion

#pragma region Events

void App::HandleOnPlayerFinishTurn()
{
	m_dungeon->m_heroEntity->isHisTurn = false;
	State* iaTurnState =
		m_gameStateMachine->GetState<IATurnState>();
	m_gameStateMachine->SwitchToState(iaTurnState);
	UpdateAllFighterPossibilities();
	Draw();
}

void App::HandleOnFinishIATurn()
{
	State* playerTurnState =
		m_gameStateMachine->GetState<PlayerTurnState>();
	m_gameStateMachine->SwitchToState(playerTurnState);
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
	if (Hero* hero = dynamic_cast<Hero*>(fighter))
	{
		m_dungeon->UpdateNearFighterPlayer();
	}
	Draw();
}

#pragma endregion

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