#pragma once
#include "Vector2D.h"
#include "Transform.h"
namespace LCF
{
	class Box
	{
	public:
		Vector2D m_LT;
		Vector2D m_RT;
		Vector2D m_LB;
		Vector2D m_RB;
		Transform m_transform;
	public:
		void SetBox(Transform _transform);
		void ModifyBox(Transform _transform);
	protected:
		void Rotate(float _angle);
		void Move(float _x, float _y);
		void Scale(float _w, float _h);
	public:
		Box();
		~Box();
	};
}

