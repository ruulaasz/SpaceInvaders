#pragma once

#include "message.h"
#include "SDL_Manager.h"

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
		BaseColliderBox(){}
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
		float m_left;
		float m_right;
		float m_top;
		float m_bot;
		float x;
		float y;
		float w;
		float h;

		float m_offsetX;
		float m_offsetY;

	public:
		void SetSize(float _x, float _y, float _w, float _h)
		{
			x = _x;
			y = _y;
			w = _w;
			h = _h;
			SetBox();
		}

		MESSAGE_LOG SetAutomaticOffset()
		{
			if (m_actor == NULL)
				return MESSAGE_WARNING("The actor is NULL");

			m_offsetX = x - m_actor->m_posX;
			m_offsetY = y - m_actor->m_posY;

			Update(0.0);

			return MESSAGE_SUCCESS("The offset is generated");
		}

		void SetOffset(float _offsetX, float _offsetY)
		{
			m_offsetX = _offsetX;
			m_offsetY = _offsetY;
		}

		virtual void Update(float /*_deltaTime*/)
		{
			if (m_actor != NULL)
			{
				if (m_centerPosition)
				{
					x = (m_actor->m_posX / w) + m_offsetX;
					y = (m_actor->m_posY / h) + m_offsetY;
				}
				else
				{
					x = m_actor->m_posX + m_offsetX;
					y = m_actor->m_posY + m_offsetY;
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
			return x;
		}

		virtual float GetY() const
		{
			return y;
		}

		virtual float GetW() const
		{
			return w;
		}

		virtual float GetH() const
		{
			return h;
		}

		virtual float GetOffsetX() const
		{
			return m_offsetX;
		}

		virtual float GetOffsetY() const
		{
			return m_offsetY;
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
			m_left = x;
			m_right = x + w;
			m_top = y;
			m_bot = y + h;
		}

	public:
		ColliderBox()
		{
			m_actor = NULL;
			m_function = NULL;
			m_centerPosition = false;
			m_enabled = true;
			m_offsetX = 0.0;
			m_offsetY = 0.0;
		}

		virtual ~ColliderBox() {};
	};
}