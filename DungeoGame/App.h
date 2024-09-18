#pragma once
#include <vector>

class Dungeon;
class StateMachine;
class PlayerController;
class IAController;

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
	void RegisterForEvents();
	void Update();

#pragma endregion

#pragma region Events

	void HandleOnPlayerFinishTurn();
	void HandleOnFinishIATurn();

#pragma endregion

};
