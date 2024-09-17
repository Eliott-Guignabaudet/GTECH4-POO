#pragma once
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

	void Update();
	void Draw();
};

