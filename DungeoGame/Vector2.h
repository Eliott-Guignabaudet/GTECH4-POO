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

#pragma region Getteur / Setteur

		void SetX(int x);
		int GetX();
		void SetY(int y);
		int GetY();

#pragma endregion

#pragma region Class function

		Vector2();
		Vector2(int x, int y);

		int GetSquareDistance(Vector2 vecOrigin, Vector2 vecTarget);
		void Normalize();

#pragma endregion

		bool operator==(const Vector2& other);

	};
}



