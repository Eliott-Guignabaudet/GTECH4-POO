#pragma once
class Fighter;

class Controller
{
public:
	Controller();
	~Controller();
	virtual void PossessFighter(Fighter* fighter);

	virtual void Update();
protected:
	Fighter* m_possessedFighter;
	
};

