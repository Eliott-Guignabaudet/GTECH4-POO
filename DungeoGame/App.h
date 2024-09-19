#pragma once
#include <vector>
#include "IAController.h"

class Dungeon;
class StateMachine;
class PlayerController;
class Fighter;

class App
{

public:
#pragma region Singleton

	App(App& other) = delete;
	void operator=(const App&) = delete;

	static App* GetInstance();

#pragma endregion

	void Run();
	void Draw();

#pragma region Getters

	PlayerController* GetPlayerController();
	std::vector<IAController*> GetIasControllers();

#pragma endregion

private:
	App();
	static App* s_instance;

#pragma region Private Attributes

	Dungeon* m_dungeon;
	StateMachine* m_gameStateMachine;
	PlayerController* m_playerController;
	std::vector<IAController*> m_iasControllers;

#pragma endregion

#pragma region Lifecycle

	void Init();
	void InitStateMachine();
	void InitDungeon(int width, int height);
	void InitControllers();

	template<typename T, typename U>
	IAController* TryCreateIAController(Fighter* fighter);

	void RegisterForEvents();
	void Update();
	void UpdateAllFighterPossibilities();

#pragma endregion

#pragma region Events

	void HandleOnPlayerFinishTurn();
	void HandleOnFinishIATurn();
	void HandleOnRedrawFighter(Fighter* fighter);

#pragma endregion

};

template<typename TestMob, typename TestBrain>
IAController* App::TryCreateIAController(Fighter* fighter)
{
	if (TestMob* mob = dynamic_cast<TestMob*>(fighter))
	{
		IAController* newIAController = new IAController();
		newIAController->PossessFighter(fighter);
		TestBrain* newBrain = new TestBrain();
		newIAController->Init(newBrain);
		return newIAController;
	}
	return nullptr;
}