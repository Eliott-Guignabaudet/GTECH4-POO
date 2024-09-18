#include "IATurnState.h"
#include "App.h"
#include "IAController.h"

void IATurnState::OnEnter()
{
	SetActiveIas(true);
}

void IATurnState::Execute()
{
}

void IATurnState::OnExit()
{
	SetActiveIas(false);
}

void IATurnState::SetActiveIas(bool isActive)
{
	std::vector<IAController*> iaControllers =
		App::GetInstance()->GetIasControllers();
	for (int i = 0; i < iaControllers.size(); i++)
	{
		iaControllers[i]->SetActive(isActive);
	}
}
