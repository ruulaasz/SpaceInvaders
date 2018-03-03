#pragma once

#include "message.h"
#include "SDL_Manager.h"
#include "Transform.h"

namespace LCF
{
	class Actor;

	class BaseColliderBox
	{
	public:
		virtual float GetLeft() const = 0;
				
		virtual float GetRight() const = 0;
			
		virtual float GetTop() const = 0;
				
		virtual float GetBot() const = 0;
				
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

		float m_left;
		float m_right;
		float m_top;
		float m_bot;

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
				SetBox();
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
				return MESSAGE_ERROR("the Target Collider is NULL");

			if (m_bot <= _target->GetTop())
				return MESSAGE_WARNING("Cant find collision");

			if (m_top >= _target->GetBot())
				return MESSAGE_WARNING("Cant find collision");

			if (m_right <= _target->GetLeft())
				return MESSAGE_WARNING("Cant find collision");

			if (m_left >= _target->GetRight())
				return MESSAGE_WARNING("Cant find collision");

			if (m_actor == NULL)
				return MESSAGE_ERROR("The Actor is NULL");

			if (m_function == NULL)
				return MESSAGE_ERROR("The Function is NULL");

			if (_target->GetActor() == NULL)
				return MESSAGE_ERROR("The target Actor is NULL");


			(m_actor->*m_function)(_target->GetActor());

			return MESSAGE_SUCCESS("Collision founded");
		}

		virtual float GetLeft() const
		{
			return m_left;
		}

		virtual float GetRight() const
		{
			return m_right;
		}

		virtual float GetTop() const
		{
			return m_top;
		}

		virtual float GetBot() const
		{
			return m_bot;
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
			m_left = m_transform.m_posX;
			m_right = m_transform.m_posX + m_transform.m_sizeW;
			m_top = m_transform.m_posY;
			m_bot = m_transform.m_posY + m_transform.m_sizeH;
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