#pragma once

namespace Maths
{
	class Vector2
	{

	public:

#pragma region Variables

		int m_x;
		int m_y;

#pragma endregion

#pragma region Class function

		Vector2();
		Vector2(int x, int y);

		static int GetDistance(Vector2 vecOrigin, Vector2 vecTarget);
		static Vector2 GetVectorDirection(Vector2 vecOrigin, Vector2 vecTarget);
		void Normalize();

#pragma endregion

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);
		//void operator+=(const Vector2& other);

	};

	//void Vector2::operator+=(const Vector2& other) 
	//{
	//	m_x += other.m_x;
	//	m_y += other.m_y;
	//}



}



