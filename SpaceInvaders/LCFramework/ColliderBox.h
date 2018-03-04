#pragma once

#include "message.h"
#include "SDL_Manager.h"
#include "Transform.h"
#include "Box.h"
#include "Vector2D.h"
namespace LCF
{
	class Actor;

	class BaseColliderBox
	{
	public:
		virtual Vector2D GetLT() const = 0;
				
		virtual Vector2D GetRT() const = 0;
				
		virtual Vector2D GetLB() const = 0;
				
		virtual Vector2D GetRB() const = 0;
				
		virtual float GetX() const = 0;
				
		virtual float GetY() const = 0;
				
		virtual float GetW() const = 0;
				
		virtual float GetH() const = 0;
				
		virtual float GetOffsetX() const = 0;
				
		virtual float GetOffsetY() const = 0;

		virtual void SetEnabled(bool _value) = 0;

		virtual bool GetEnabled() const = 0;

		virtual Actor* GetActor() const = 0;

		virtual Uint64 GetID() const = 0;

		virtual void SetId(Uint64 _ID) = 0;

		virtual void Update(float _deltaTime) = 0;

		virtual void Destroy() = 0;

		virtual MESSAGE_LOG CheckCollision(const BaseColliderBox* _target) = 0;

	public:
		BaseColliderBox() {}
		virtual ~BaseColliderBox() {}
	};

	template<class _type>
	class ColliderBox : public BaseColliderBox
	{
	protected:
		Uint64 m_ID;
		_type* m_actor;
		void(_type::*m_function)(const Actor*);
		bool m_centerPosition;
		bool m_enabled;

		bool m_followActor;
		bool m_resizeActor;
		bool m_rotateActor;

		Box m_boundingBounds;
		Transform m_transform;

		Transform m_transformOffset;

	public:
		void SetFlags(bool _followActor, bool _automaticResize, bool _automaticRotate)
		{
			m_followActor = _followActor;
			m_resizeActor = _automaticResize;
			m_rotateActor = _automaticRotate;
		}

		void SetSize(float _x, float _y, float _w, float _h, float _angle = 0.0f)
		{
			m_transform.m_posX = _x;
			m_transform.m_posY = _y;
			m_transform.m_sizeW = _w;
			m_transform.m_sizeH = _h;
			m_transform.m_angle = _angle;
			SetBox();
		}

		void SetSize(Transform _transform)
		{
			m_transform = _transform;
			SetBox();
		}

		MESSAGE_LOG SetAutomaticOffset()
		{
			if (m_actor == NULL)
				return MESSAGE_WARNING("The actor is NULL");

			m_transformOffset.m_posX = m_transform.m_posX - m_actor->m_transform.m_posX;
			m_transformOffset.m_posY = m_transform.m_posY - m_actor->m_transform.m_posY;

			m_transformOffset.m_sizeW = m_transform.m_sizeW - m_actor->m_transform.m_sizeW;
			m_transformOffset.m_sizeH = m_transform.m_sizeH - m_actor->m_transform.m_sizeH;

			m_transformOffset.m_angle = m_transform.m_angle - m_actor->m_transform.m_angle;

			Update(0.0f);

			return MESSAGE_SUCCESS("The offset is generated");
		}

		void SetOffset(float _offsetX, float _offsetY, float _offsetW = 0.0f, float _offsetH = 0.0f, float _offsetAngle = 0.0f)
		{
			m_transformOffset.m_posX = _offsetX;
			m_transformOffset.m_posY = _offsetY;

			m_transformOffset.m_sizeW = _offsetW;
			m_transformOffset.m_sizeH = _offsetH;

			m_transformOffset.m_angle = _offsetAngle;

			Update(0.0f);
		}

		void SetOffset(Transform _offset)
		{
			m_transformOffset = _offset;

			Update(0.0f);
		}

		virtual void Update(float /*_deltaTime*/)
		{
			if (m_actor != NULL)
			{
				if (m_followActor)
				{
					if (m_centerPosition)
					{
						m_transform.m_posX = (m_actor->m_transform.m_posX / m_transform.m_sizeW) + m_transformOffset.m_posX;
						m_transform.m_posY = (m_actor->m_transform.m_posY / m_transform.m_sizeH) + m_transformOffset.m_posY;
					}
					else
					{
						m_transform.m_posX = m_actor->m_transform.m_posX + m_transformOffset.m_posX;
						m_transform.m_posY = m_actor->m_transform.m_posY + m_transformOffset.m_posY;
					}
				}
				if (m_resizeActor)
				{
					m_transform.m_sizeW = m_actor->m_transform.m_sizeW + m_transformOffset.m_sizeW;
					m_transform.m_sizeH = m_actor->m_transform.m_sizeH + m_transformOffset.m_sizeH;
				}
				if (m_rotateActor)
				{
					m_transform.m_angle = m_actor->m_transform.m_angle + m_transformOffset.m_angle;
				}
				ModifyBox();
			}
		}

		virtual void Destroy()
		{
			m_actor = NULL;
			m_function = NULL;
			m_enabled = false;
		}

		MESSAGE_LOG SetActor(Actor* _actor, bool _centerPosition = false)
		{
			if (_actor == NULL)
				return MESSAGE_WARNING("The object is NULL");

			if (m_actor != NULL)
				return MESSAGE_WARNING("The Collider already had a object");

			m_actor = (_type*)_actor;
			m_centerPosition = _centerPosition;
			return MESSAGE_SUCCESS("Success to set the object");
		}

		MESSAGE_LOG SetFunction(void(_type::*_foo)(const Actor*))
		{
			if (m_function != NULL)
				return MESSAGE_WARNING("Already had an fuction");
			m_function = _foo;
			return MESSAGE_SUCCESS("Added Correctly");
		}

		virtual MESSAGE_LOG CheckCollision(const BaseColliderBox* _ColliderBox)
		{
			const ColliderBox<_type>* _target = (const ColliderBox<_type>*)_ColliderBox;

			if (_target == NULL)
				return MESSAGE_ERROR("The Target Collider is NULL");

			if (m_actor == NULL)
				return MESSAGE_ERROR("The Actor is NULL");

			if (m_function == NULL)
				return MESSAGE_ERROR("The Function is NULL");

			if (_target->GetActor() == NULL)
				return MESSAGE_ERROR("The target Actor is NULL");
			
			float minX1 = min(min(m_boundingBounds.m_LT.m_x, m_boundingBounds.m_LB.m_x), min(m_boundingBounds.m_RT.m_x, m_boundingBounds.m_RB.m_x));
			float maxX1 = max(max(m_boundingBounds.m_LT.m_x, m_boundingBounds.m_LB.m_x), max(m_boundingBounds.m_RT.m_x, m_boundingBounds.m_RB.m_x));
			float minY1 = min(min(m_boundingBounds.m_LT.m_y, m_boundingBounds.m_LB.m_y), min(m_boundingBounds.m_RT.m_y, m_boundingBounds.m_RB.m_y));
			float maxY1 = max(max(m_boundingBounds.m_LT.m_y, m_boundingBounds.m_LB.m_y), max(m_boundingBounds.m_RT.m_y, m_boundingBounds.m_RB.m_y));
			
			float minX2 = min(min(_target->GetLT().m_x, _target->GetRT().m_x), min(_target->GetLB().m_x, _target->GetRB().m_x));
			float maxX2 = max(max(_target->GetLT().m_x, _target->GetRT().m_x), max(_target->GetLB().m_x, _target->GetRB().m_x));
			float minY2 = min(min(_target->GetLT().m_y, _target->GetRT().m_y), min(_target->GetLB().m_y, _target->GetRB().m_y));
			float maxY2 = max(max(_target->GetLT().m_y, _target->GetRT().m_y), max(_target->GetLB().m_y, _target->GetRB().m_y));

			if (maxX1 <= minX2 || minX1 >= maxX2)
				return MESSAGE_WARNING("Cant find collision");

			if(	maxY1 <= minY2 || minY1 >= maxY2)
				return MESSAGE_WARNING("Cant find collision");

			(m_actor->*m_function)(_target->GetActor());

			return MESSAGE_SUCCESS("Collision founded");
		}

		virtual Vector2D GetLT() const
		{
			return m_boundingBounds.m_LT;
		}

		virtual Vector2D GetRT() const
		{
			return m_boundingBounds.m_RT;
		}

		virtual Vector2D GetLB() const
		{
			return m_boundingBounds.m_LB;
		}

		virtual Vector2D GetRB() const
		{
			return m_boundingBounds.m_RB;
		}

		virtual Actor* GetActor() const
		{
			return m_actor;
		}

		virtual float GetX() const
		{
			return m_transform.m_posX;
		}

		virtual float GetY() const
		{
			return m_transform.m_posY;
		}

		virtual float GetW() const
		{
			return m_transform.m_sizeW;
		}

		virtual float GetH() const
		{
			return m_transform.m_sizeH;
		}

		virtual float GetOffsetX() const
		{
			return m_transformOffset.m_posX;
		}

		virtual float GetOffsetY() const
		{
			return m_transformOffset.m_posY;
		}

		virtual void SetEnabled(bool _value)
		{
			m_enabled = _value;
		}

		virtual bool GetEnabled() const
		{
			return m_enabled;
		}

		virtual Uint64 GetID() const
		{
			return m_ID;
		}

		virtual void SetId(Uint64 _ID)
		{
			m_ID = _ID;
		}

	protected:
		void SetBox()
		{
			m_boundingBounds.SetBox(m_transform);
		}
		void ModifyBox()
		{
			m_boundingBounds.ModifyBox(m_transform);
		}

	public:
		ColliderBox() : m_followActor(true),
			m_resizeActor(true),
			m_rotateActor(true),
			m_actor(NULL),
			m_centerPosition(false),
			m_enabled(true)
		{
			m_function = NULL;
		}

		virtual ~ColliderBox() {};
	};
}