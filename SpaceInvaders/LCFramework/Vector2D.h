#pragma once
namespace LCF
{
	class Vector2D
	{
	public:
		float m_x;
		float m_y;
	public:
		bool operator<=(const Vector2D _other);
		bool operator>=(const Vector2D _other);
	public:
		Vector2D();
		~Vector2D();
	};
}

