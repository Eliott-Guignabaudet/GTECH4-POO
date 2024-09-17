#include <iostream>

#include "App.h"
#include "Time.h"
#include "Dungeon.h"

#pragma region StateMachine Includes
#include "StateMachine.h"
#include "InitState.h"
#include "PlayerTurnState.h"
#include "IATurnState.h"
#include "GameOverState.h"
#pragma endregion


App* App::s_instance = nullptr;

App::App() :
	m_gameStateMachine(nullptr),
	m_dungeon(nullptr)
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

void App::Run()
{
	std::cout << "Start Application" << std::endl;
	Time::GetInstance()->StartTime();
	Init();
	Draw();
	while (true)
	{
		if (Time::GetInstance()->UpdateTime())
		{
			Update(); 
		}
	}
	
}
#pragma region Lifecycle

void App::Init()
{
	m_dungeon = new Dungeon();
	m_gameStateMachine = new StateMachine();

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
}

void App::Update()
{
	// TODO: Update
	// 
}

void App::Draw()
{
	// system("cls");

	// TODO: Draw Function
	//		 Draw Title
	//		 Draw CurrentTurn
	//		 Draw Dungeon
	//		 Draw Player Actions
	//		 Draw Last events

	std::cout 
		<< Time::GetInstance()->GetElapsedTime() 
		<< std::endl;
}

#pragma endregion