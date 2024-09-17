#include "Time.h"


const int FPS_MAX = 30;

#pragma region Singleton
Time* Time::s_instance = nullptr;

Time::Time() : 
	m_isStarted(false),
	m_sysTime(),
	m_elapsedTime(),
	m_deltaTime(),
	m_timeScale()
{

}

Time* Time::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Time();
	}
	return s_instance;
}
#pragma endregion

void Time::StartTime()
{
	if (m_isStarted)
	{
		return;
	}
	DWORD time = timeGetTime();

	m_elapsedTime = 0;
	m_deltaTime = 0;
	m_timeScale = 1;
	m_sysTime = time;
	m_isStarted = true;
}

bool Time::UpdateTime()
{
	DWORD newTime = timeGetTime();
	DWORD elapsedTime = newTime - m_sysTime;
	if (elapsedTime < 1000 / FPS_MAX)
	{
		return false;
	}
	m_deltaTime = elapsedTime / 1000.f;
	m_elapsedTime += m_deltaTime;
	m_sysTime = newTime;
	return true;
}

#pragma region Getters

float Time::GetScaledDeltaTime()
{
	return m_deltaTime * m_timeScale;
}

float Time::GetElapsedTime()
{
	return m_elapsedTime;
}

float Time::GetTimeScale()
{
	return m_timeScale;
}


#pragma endregion

#pragma region Setters

void Time::SetTimeScale(float timeScale)
{
	m_timeScale = timeScale;
}

#pragma endregion