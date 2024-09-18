#include <Windows.h>
#include "PlayerController.h"
#include "Hero.h"
#include "Input.h"
#include "App.h"

using namespace Maths;
void PlayerController::PossessFighter(Fighter* fighter)
{
	Hero* hero = dynamic_cast<Hero*>(fighter);
	if (!hero)
	{
		return;
	}
	Controller::PossessFighter(fighter);
}

void PlayerController::Update()
{
	if (!m_isActive || !m_possessedFighter) 
	{
		return;
	}
	HandleInput();

}

void PlayerController::HandleInput()
{
	Vector2 newdir = Vector2(0, 0);
	HandleInputDirection(newdir);
	HandleInputFinishTurn();
	MovePlayer(newdir);
	
}

void PlayerController::HandleInputDirection(Vector2& direction)
{
	if (Input::IsKeyPush(VK_UP))
	{
		direction = Vector2(0, -1);
	}
	if (Input::IsKeyPush(VK_DOWN))
	{
		direction = Vector2(0, 1);
	}
	if (Input::IsKeyPush(VK_LEFT))
	{
		direction = Vector2(-1, 0);
	}
	if (Input::IsKeyPush(VK_RIGHT))
	{
		direction = Vector2(1, 0);
	}
}

void PlayerController::HandleInputFinishTurn()
{
	if (Input::IsKeyPush(VK_SPACE))
	{
		if (OnFinishTurn)
		{
			OnFinishTurn();
		}
		//App::GetInstance()->Draw();
	}
	if (Input::IsKeyPush(VK_RETURN))
	{
		// TODO : Execute Attack
		//App::GetInstance()->Draw();
	}
}

void PlayerController::MovePlayer(Vector2 direction)
{
	// TODO : Change Move

	m_possessedFighter->SetDirection(direction);

	if (direction.m_x != 0 || direction.m_y != 0)
	{
		m_possessedFighter->Move();
		//App::GetInstance()->Draw();
	}
}
