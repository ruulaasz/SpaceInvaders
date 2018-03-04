#include "Box.h"
#include <math.h>
namespace LCF
{
	void Box::SetBox(Transform _transform)
	{
		m_transform = _transform;

		m_LT.m_x = _transform.m_posX;
		m_LT.m_y = _transform.m_posY;

		m_RT.m_x = _transform.m_posX + _transform.m_sizeW;
		m_RT.m_y = _transform.m_posY;

		m_LB.m_x = _transform.m_posX;
		m_LB.m_y = _transform.m_posY + _transform.m_sizeH;

		m_RB.m_x = _transform.m_posX + _transform.m_sizeW;
		m_RB.m_y = _transform.m_posY + _transform.m_sizeH;

		Rotate(_transform.m_angle);
	}
	void Box::ModifyBox(Transform _transform)
	{
		if (_transform.m_posX != m_transform.m_posX || _transform.m_posY != m_transform.m_posY ||
			_transform.m_sizeW != m_transform.m_sizeW || _transform.m_sizeH != m_transform.m_sizeH ||
			_transform.m_angle != m_transform.m_angle)
		{
			//Move(_transform.m_posX, _transform.m_posY);
			SetBox(_transform);
		}
	}
	void Box::Rotate(float _angle)
	{
		float centerColliderX = m_transform.m_posX + m_transform.m_sizeW / 2;
		float centerColliderY = m_transform.m_posY + m_transform.m_sizeH / 2;
		float angle = _angle * 3.14159265358979323846 / 180;
		Vector2D lt = m_LT;
		Vector2D rt = m_RT;
		Vector2D lb = m_LB;
		Vector2D rb = m_RB;

		m_LT.m_x = (lt.m_x - centerColliderX) * cos(angle) - (lt.m_y - centerColliderY) * sin(angle) + centerColliderX;
		m_LT.m_y = (lt.m_x - centerColliderX) * sin(angle) + (lt.m_y - centerColliderY) * cos(angle) + centerColliderY;

		m_RT.m_x = (rt.m_x - centerColliderX) * cos(angle) - (rt.m_y - centerColliderY) * sin(angle) + centerColliderX;
		m_RT.m_y = (rt.m_x - centerColliderX) * sin(angle) + (rt.m_y - centerColliderY) * cos(angle) + centerColliderY;

		m_LB.m_x = (lb.m_x - centerColliderX) * cos(angle) - (lb.m_y - centerColliderY) * sin(angle) + centerColliderX;
		m_LB.m_y = (lb.m_x - centerColliderX) * sin(angle) + (lb.m_y - centerColliderY) * cos(angle) + centerColliderY;

		m_RB.m_x = (rb.m_x - centerColliderX) * cos(angle) - (rb.m_y - centerColliderY) * sin(angle) + centerColliderX;
		m_RB.m_y = (rb.m_x - centerColliderX) * sin(angle) + (rb.m_y - centerColliderY) * cos(angle) + centerColliderY;
	}
	void Box::Move(float _x, float _y)
	{
		m_LT.m_x = _x;
		m_LT.m_y = _y;

		m_RT.m_x = _x;
		m_RT.m_y = _y;

		m_LB.m_x = _x;
		m_LB.m_y = _y;

		m_RB.m_x = _x;
		m_RB.m_y = _y;
	}
	void Box::Scale(float _w, float _h)
	{
		m_RT.m_x += _w;
		
		m_LB.m_y += _h;

		m_RB.m_x += _w;
		m_RB.m_y += _h;
	}
	Box::Box()
	{
	}


	Box::~Box()
	{
	}
}