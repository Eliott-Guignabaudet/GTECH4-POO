#include <iostream>
#include "PlayerTurnState.h"
#include "App.h"
#include "PlayerController.h"

void PlayerTurnState::OnEnter()
{
	std::cout << "Enter Player turn state" << std::endl;
	App::GetInstance()->GetPlayerController()->SetActive(true);
}

void PlayerTurnState::Execute()
{
}

void PlayerTurnState::OnExit()
{
	App::GetInstance()->GetPlayerController()->SetActive(false);
}
