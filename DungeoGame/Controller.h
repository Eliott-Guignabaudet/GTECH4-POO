#pragma once
class Fighter;

class Controller
{
public:
	Controller();
	~Controller();
	virtual void PossessFighter(Fighter* fighter);

	virtual void Update();

	bool GetIsActive();
	void SetActive(bool isActive);

protected:
	Fighter* m_possessedFighter;
	bool m_isActive;
};

