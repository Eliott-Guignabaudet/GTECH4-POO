#include "Controller.h"

Controller::Controller() : 
	m_possessedFighter(nullptr),
	m_isActive(false)
{
}

Controller::~Controller()
{
}

void Controller::PossessFighter(Fighter* fighter)
{
	m_possessedFighter = fighter;
}

void Controller::Update()
{
}

bool Controller::GetIsActive()
{
	return m_isActive;
}

void Controller::SetActive(bool isActive)
{
	m_isActive = isActive;
}
