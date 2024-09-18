#include <iostream>

#include "App.h"
#include "Time.h"
#include "Dungeon.h"
#include "Input.h"
#include "PlayerController.h"
#include "Fighter.h"
#include "Hero.h"

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
	int width = 119;
	int height = 20;
	m_dungeon = new Dungeon(width, height);
	m_dungeon->SpawnPlayer(width / 2, height / 2);
	m_dungeon->SpawnMob();

	m_gameStateMachine = new StateMachine();
	m_playerController = new PlayerController();
	m_playerController->PossessFighter(m_dungeon->m_heroEntity);

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

void App::RegisterForEvents()
{
	auto onPlayerFinishTurnBind =
		std::bind( &App::HandleOnPlayerFinishTurn, this);
	m_playerController->OnFinishTurn = onPlayerFinishTurnBind;

	auto onIaTurnFinishBind =
		std::bind(&App::HandleOnFinishIATurn, this);
	IATurnState* iaTurnState =
		m_gameStateMachine->GetState<IATurnState>();
	iaTurnState->OnFinishIATurn = onIaTurnFinishBind;

	auto onFighterMovedBind =
		std::bind(&App::HandleOnFighterMoved, this, _1);
	Fighter::OnFighterMoved = onFighterMovedBind;
}

void App::Update()
{
	m_playerController->Update();
	m_gameStateMachine->Update();
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
	// TODO: Draw Function
	//		 Draw Title
	//		 Draw CurrentTurn
	//		 Draw Dungeon
	m_dungeon->Draw();
	//		 Draw Player Actions
	//		 Draw Last events

	std::cout 
		<< Time::GetInstance()->GetElapsedTime() 
		<< std::endl;
}

#pragma endregion

#pragma region Events

void App::HandleOnPlayerFinishTurn()
{
	State* iaTurnState =
		m_gameStateMachine->GetState<IATurnState>();
	m_gameStateMachine->SwitchToState(iaTurnState);
	Draw();
}

void App::HandleOnFinishIATurn()
{
	State* playerTurnState =
		m_gameStateMachine->GetState<PlayerTurnState>();
	m_gameStateMachine->SwitchToState(playerTurnState);
	Draw();
}

void App::HandleOnFighterMoved(Fighter* fighter)
{
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