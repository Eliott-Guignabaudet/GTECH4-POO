#include <Windows.h>
#include "PlayerController.h"
#include "Hero.h"
#include "Input.h"

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
	if (!m_possessedFighter) 
	{
		return;
	}
	Vector2 newdir = Vector2(0,0);
	if (Input::IsKeyPush(VK_UP))
	{
		newdir = Vector2(0, 1);
	}
	if (Input::IsKeyPush(VK_DOWN))
	{
		newdir = Vector2(0, -1);
	}
	if (Input::IsKeyPush(VK_LEFT))
	{
		newdir = Vector2(-1, 0);
	}
	if (Input::IsKeyPush(VK_RIGHT))
	{
		newdir = Vector2(1, 0);
	}
	m_possessedFighter->SetDirection(newdir);
	// TODO : Move

}
