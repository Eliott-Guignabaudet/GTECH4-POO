#include <Windows.h>
#include "Input.h"

KeyState* Input::m_keyStates = Input::GenerateStates();

KeyState* Input::GenerateStates()
{
	KeyState* ptr = new KeyState[256];
	for (int i = 0; i < 256; i++)
	{
		ptr[i] = KeyState::NONE;
	}
	return ptr;
}

void Input::Init()
{

}

void Input::UpdateKeyStates()
{
	for (int i = 0; i < 256; i++)
	{

		SHORT keyState = GetAsyncKeyState(i);
		if (keyState)
		{
			switch (m_keyStates[i])
			{
			case KeyState::NONE:
				m_keyStates[i] = KeyState::PUSH;
				break;
			case KeyState::UP:
				m_keyStates[i] = KeyState::PUSH;
				break;
			case KeyState::PUSH:
				m_keyStates[i] = KeyState::DOWN;
				break;
			}
		}
		else
		{
			m_keyStates[i] = KeyState::UP;
		}
	}
}

KeyState Input::GetKeyStyate(int a_index)
{
	return m_keyStates[a_index];
}

bool Input::IsKeyDown(int a_index)
{
	return m_keyStates[a_index] == KeyState::DOWN;
}

bool Input::IsKeyPush(int a_index)
{
	return m_keyStates[a_index] == KeyState::PUSH;
}

bool Input::IsKeyUp(int a_index)
{
	return m_keyStates[a_index] == KeyState::UP;
}

bool Input::IsKey(int a_index)
{
	return m_keyStates[a_index] == KeyState::DOWN
		|| m_keyStates[a_index] == KeyState::PUSH;
}
