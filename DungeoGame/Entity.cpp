#include "Entity.h"
#include <iostream>

int Entity::s_currentEntityIndex = 0;

#pragma region Getteur / Setteur

void Entity::SetPosition(Vector2 pos)
{
	m_pos = pos;
}

Vector2& Entity::GetPosition()
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

int Entity::GetId()
{
	return m_id;
}

std::string Entity::GetName()
{
	return m_name;
}

#pragma endregion

#pragma region Class function

Entity::Entity() :
	m_pos(0, 0),
	m_sprite(' '),
	m_id(Entity::s_currentEntityIndex++),
	m_name("Entity")
{

}

Entity::Entity(Vector2 pos, char sprite) :
	m_pos(pos),
	m_sprite(sprite),
	m_id(Entity::s_currentEntityIndex++),
	m_name("Entity")
{

}

void Entity::Draw()
{
	std::cout << m_sprite;
}

#pragma endregion
