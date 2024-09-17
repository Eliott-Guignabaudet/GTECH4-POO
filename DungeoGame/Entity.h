#pragma once
#include "Vector2.h"

class Entity
{
public:

#pragma region Variables

	Maths::Vector2* m_pos;

	char m_sprite;

#pragma endregion

#pragma region Getteur / Setteur

	void SetPosition(Maths::Vector2* pos);
	Maths::Vector2* GetPosition();

	void SetSprite(char sprite);
	char GetSprite();

#pragma endregion

#pragma region Class function

	Entity();
	Entity(Maths::Vector2* pos, char sprite = ' ');

	void Draw();

#pragma endregion
};

