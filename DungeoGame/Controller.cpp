#include "Controller.h"

Controller::Controller() : m_possessedFighter(nullptr)
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
