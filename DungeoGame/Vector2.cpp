#include "Vector2.h"
#include <cmath>

Maths::Vector2::Vector2() :
    m_x(0),
    m_y(0)
{

}

Maths::Vector2::Vector2(int x, int y) :
    m_x(x),
    m_y(y)
{

}

int Maths::Vector2::GetDistance(Vector2 vecOrigin, Vector2 vecTarget)
{
    int xSquare = (vecTarget.m_x - vecOrigin.m_x);
    int ySquare = (vecTarget.m_y - vecOrigin.m_y);

    return xSquare + ySquare;
}

Maths::Vector2 Maths::Vector2::GetVectorDirection(Vector2 vecOrigin, Vector2 vecTarget)
{
    int xSquare = (vecTarget.m_x - vecOrigin.m_x);
    int ySquare = (vecTarget.m_y - vecOrigin.m_y);

    return Maths::Vector2(xSquare, ySquare);
}

void Maths::Vector2::Normalize()
{
    // Compute the magnitude of the vector
    int magnitude = std::sqrt(m_x * m_x + m_y * m_y);

    // Check for zero magnitude to avoid division by zero
    if (magnitude != 0)
    {
        m_x /= magnitude;
        m_y /= magnitude;
    }
}

bool Maths::Vector2::operator==(const Vector2& other)
{
    return m_x == other.m_x && m_y == other.m_y;
}

bool Maths::Vector2::operator!=(const Vector2& other)
{
    return !(*this == other);
    //return m_x != other.m_x || m_y != other.m_y;
}



