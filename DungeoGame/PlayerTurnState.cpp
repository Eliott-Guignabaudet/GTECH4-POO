#include <iostream>
#include "PlayerTurnState.h"

void PlayerTurnState::OnEnter()
{
	std::cout << "Enter Player turn state" << std::endl;
	// TODO: Enable Player controller
}

void PlayerTurnState::Execute()
{
}

void PlayerTurnState::OnExit()
{
	// TODO: Disable Player Controller 
}
