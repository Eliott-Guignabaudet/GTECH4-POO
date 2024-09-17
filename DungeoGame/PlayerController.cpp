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
	if (!m_possessedFighter) 
	{
		return;
	}
	Vector2 newdir = Vector2(0,0);
	if (Input::IsKeyPush(VK_UP))
	{
		newdir = Vector2(0, -1);
	}
	if (Input::IsKeyPush(VK_DOWN))
	{
		newdir = Vector2(0, 1);
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
	Vector2* pos = m_possessedFighter->GetPosition();
	pos->m_x += newdir.m_x;
	pos->m_y += newdir.m_y;
	if (newdir.m_x != 0 || newdir.m_y != 0)
	{
		App::GetInstance()->Draw();
	}
	// TODO : Move

}
