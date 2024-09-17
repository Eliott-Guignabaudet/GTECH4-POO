#include "Entity.h"
#include <iostream>

#pragma region Getteur / Setteur

void Entity::SetPosition(Maths::Vector2 pos)
{
	m_pos = pos;
}

Maths::Vector2 Entity::GetPosition()
{
	return m_pos;
}

void Entity::SetSprite(char sprite)
{
	m_sprite = sprite;
}

char Entity::GetSprite()
{
	return m_sprite;
}

#pragma endregion

#pragma region Class function

Entity::Entity() :
	m_pos(0, 0),
	m_sprite(' ')
{

}

Entity::Entity(Maths::Vector2 pos, char sprite) :
	m_pos(pos),
	m_sprite(sprite)
{

}

void Entity::Draw()
{
	std::cout << m_sprite;
}

#pragma endregion
