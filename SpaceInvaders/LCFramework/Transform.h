#pragma once
namespace LCF
{
	class Transform
	{
	public:
		float m_posX;
		float m_posY;
		float m_sizeW;
		float m_sizeH;
		float m_angle;
	public:
		Transform();
		Transform(float _posX, float _posY, float _sizeW, float _sizeH, float _angle);
		~Transform();
	};
}

