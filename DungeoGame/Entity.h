#pragma once
#include "Vector2.h"

using namespace Maths;

class Entity
{
private:
	static int s_currentEntityIndex;
	int m_id;
protected :
#pragma region Variables

	Vector2 m_pos;

	char m_sprite;

#pragma endregion

public:
#pragma region Getteur / Setteur

	void SetPosition(Vector2 pos);
	Vector2& GetPosition();

	void SetSprite(char sprite);
	char GetSprite();

	int GetId();
#pragma endregion

#pragma region Class function

	Entity();
	Entity(Vector2 pos, char sprite = ' ');

	virtual ~Entity() = default; // Ajoutez ce destructeur virtuel

	void Draw();

#pragma endregion
};

