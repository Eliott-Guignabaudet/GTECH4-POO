#include "Dungeon.h"
#include <iostream>

Dungeon::Dungeon() :
    m_defaultEntity(nullptr),
    m_weightDungeon(0),
    m_heightDungeon(0),
    m_horizontalWall(' '),
    m_verticalWall(' '),
    m_cornerWall(' ')
{

}

Dungeon::Dungeon(int weight, int height, char cornerWall, char horizontalWall, char verticalWall) :
    m_weightDungeon(weight),
    m_heightDungeon(height),
    m_cornerWall(cornerWall),
    m_horizontalWall(horizontalWall),
    m_verticalWall(verticalWall)
{
    m_defaultEntity = new Entity();
    m_entities = std::vector<Entity*>();
}

void Dungeon::Clear()
{
    for (Entity* entity : m_entities)
    {
        delete entity;
    }

    m_entities.clear();
}

void Dungeon::AddEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void Dungeon::RemoveEntity(Entity* entity)
{
    for (auto it = m_entities.begin(); it != m_entities.end();)
    {
        if (*it == entity)
        {
            delete* it;
            it = m_entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool Dungeon::DrawLimitBounds(bool xlimit, bool ylimit) 
{
    if (xlimit && ylimit)
    {
        std::cout << m_cornerWall;
    }
    else if (ylimit)
    {
        std::cout << m_horizontalWall;
    }
    else if (xlimit)
    {
        std::cout << m_verticalWall;
    }
    else 
    {
        return false;
    }
    return true;
}

void Dungeon::Draw()
{
    for (size_t i = 0; i <= m_heightDungeon; i++)
    {
        bool yIsInLimit = (i == 0 || i == m_heightDungeon);

        for (size_t j = 0; j <= m_weightDungeon; i++)
        {
            bool xIsInLimit = (j == 0 || j == m_weightDungeon);

            bool isDrawLimitBounds = DrawLimitBounds(xIsInLimit, yIsInLimit);

            if (!isDrawLimitBounds) 
            {
                bool isDefaultEntity = true;
                for (Entity* entity : m_entities)
                {
                    if (entity->GetPosition() == Maths::Vector2(i, j)) 
                    {
                        isDefaultEntity = false;
                        entity->Draw();
                        break;
                    }
                }

                if (isDefaultEntity) {
                    m_defaultEntity->Draw();
                }
            }
        }
    }
}
