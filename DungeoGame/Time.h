#pragma once
#include <Windows.h>

class Time
{
private:
	Time();
	static Time* s_instance;

	bool m_isStarted;
	DWORD m_sysTime;
	float m_elapsedTime;
	float m_deltaTime;
	float m_timeScale;

public:
	Time(Time& other) = delete;
	void operator=(const Time&) = delete;
	
	
	static Time* GetInstance();

	void StartTime();

	bool UpdateTime();

	float GetScaledDeltaTime();
	float GetElapsedTime();
	float GetTimeScale();

	void SetTimeScale(float timeScale);
};

