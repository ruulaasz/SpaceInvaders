#include "Vector2D.h"


namespace LCF
{
	bool Vector2D::operator<=(const Vector2D _other)
	{
		return (m_x <= _other.m_x && m_y <= _other.m_y);
	}
	bool Vector2D::operator>=(const Vector2D _other)
	{
		return (m_x >= _other.m_x && m_y >= _other.m_y);
	}
	Vector2D::Vector2D()
	{
		m_x = 0.0f;
		m_y = 0.0f;
	}


	Vector2D::~Vector2D()
	{
	}

}