#pragma once
#include <vector>
class Dungeon;
class StateMachine;

class App
{

public:
	App(App& other) = delete;
	void operator=(const App&) = delete;

	static App* GetInstance();
	void Run();


private:
	App();
	static App* s_instance;
	Dungeon* m_dungeon;
	StateMachine* m_gameStateMachine;

	void Init();
	void Update();
	void Draw();
};
