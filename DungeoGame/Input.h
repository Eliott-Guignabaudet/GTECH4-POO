#pragma once
enum class KeyState
{
	NONE,
	UP,
	PUSH,
	DOWN
};


class Input
{
public:
	static void Init();
	static void UpdateKeyStates();
	static KeyState GetKeyStyate(int a_index);
	static bool IsKeyDown(int a_index);
	static bool IsKeyPush(int a_index);
	static bool IsKeyUp(int a_index);
	static bool IsKey(int a_index);
private:
	static KeyState* GenerateStates();
	static KeyState* m_keyStates;
};

