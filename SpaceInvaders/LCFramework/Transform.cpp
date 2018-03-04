#include "Transform.h"

namespace LCF
{
	Transform::Transform()
	{
		m_posX = 0.0f;
		m_posY = 0.0f;
		m_sizeW = 0.0f;
		m_sizeH = 0.0f;
		m_angle = 0.0f;
	}

	Transform::Transform(float _posX, float _posY, float _sizeW, float _sizeH, float _angle)
	{
		m_posX = _posX;
		m_posY = _posY;
		m_sizeW = _sizeW;
		m_sizeH = _sizeH;
		m_angle = _angle;
	}


	Transform::~Transform()
	{
	}
}