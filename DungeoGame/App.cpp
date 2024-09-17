#include <iostream>

#include "App.h"
#include "Time.h"

App* App::s_instance = nullptr;

App::App() 
{

}

App* App::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new App();
	}
    return s_instance;
}

void App::Run()
{
	std::cout << "Start Application" << std::endl;
	Time::GetInstance()->StartTime();
	Draw();
	while (true)
	{
		if (Time::GetInstance()->UpdateTime())
		{
			Update(); 
		}
	}
	
}


void App::Update()
{
}

void App::Draw()
{
	system("cls");
	std::cout << Time::GetInstance()->GetElapsedTime() << std::endl;
}