#pragma once
#include "message.h"

namespace LCF
{
	class Actor;

	class BaseColliderBox
	{
	public:
		virtual int GetLeft() const = 0;

		virtual int GetRight() const = 0;

		virtual int GetTop() const = 0;

		virtual int GetBot() const = 0;

		virtual int GetX() const = 0;

		virtual int GetY() const = 0;

		virtual int GetW() const = 0;

		virtual int GetH() const = 0;

		virtual void SetEnabled(bool _value) = 0;

		virtual bool GetEnabled() const = 0;

		//virtual void SetRendered(bool _value) = 0;

		//virtual bool GetRenderer() const = 0;

		virtual Actor* GetActor() const = 0;

		virtual void Update(float _deltaTime) = 0;

		virtual MESSAGE_LOG CheckCollision(const BaseColliderBox* _target) = 0;

	public:
		BaseColliderBox(){}
		virtual ~BaseColliderBox() {}
	};

	template<class _type>
	class ColliderBox : public BaseColliderBox
	{
	protected:
		_type* m_actor;
		void(_type::*m_function)(const Actor*);
		bool m_centerPosition;
		bool m_enabled;
		//bool m_rendered;
		int m_left;
		int m_right;
		int m_top;
		int m_bot;

	public:
		union 
		{
			struct 
			{
				int x;
				int y;
				int w;
				int h;
			};
			int line[4];
		};

	public:
		void SetSize(int _x, int _y, int _w, int _h)
		{
			x = _x;
			y = _y;
			w = _w;
			h = _h;
			//std::cout << x << " " << y << " " << w << " " << h << "\n";
			SetBox();

		}

		void SetSize(int _line[4])
		{
			line[0] = _line[0];
			line[1] = _line[1];
			line[2] = _line[2];
			line[3] = _line[3];
			SetBox();
		}

		virtual void Update(float _deltaTime)
		{
			if (m_actor != NULL)
			{
				if (m_centerPosition)
				{
					x = m_actor->m_posX / w;
					y = m_actor->m_posY / h;
				}
				else
				{
					x = m_actor->m_posX;
					y = m_actor->m_posY;
				}
				SetBox();
			}
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
			ENABLE_PRINT_MESSAGE(false);
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

		virtual int GetLeft() const
		{
			return m_left;
		}

		virtual int GetRight() const
		{
			return m_right;
		}

		virtual int GetTop() const
		{
			return m_top;
		}

		virtual int GetBot() const
		{
			return m_bot;
		}

		virtual Actor* GetActor() const
		{
			return m_actor;
		}

		virtual int GetX() const
		{
			return x;
		}

		virtual int GetY() const
		{
			return y;
		}

		virtual int GetW() const
		{
			return w;
		}

		virtual int GetH() const
		{
			return y;
		}

		virtual void SetEnabled(bool _value)
		{
			m_enabled = _value;
		}

		virtual bool GetEnabled() const
		{
			return m_enabled;
		}

		/*virtual void SetRenderer(bool _value)
		{
			m_rendered = _value;
		}

		virtual bool GetRendered() const
		{
			return m_rendered;
		}*/

	protected:
		void SetBox()
		{
			m_left = x;
			m_right = x + w;
			m_top = y;
			m_bot = y + h;
			//std::cout << m_left << " " << m_right << " " << m_top << " " << m_bot << "\n";
		}

	public:
		ColliderBox()
		{
			m_actor = NULL;
			m_function = NULL;
			m_centerPosition = false;
			m_enabled = true;
			//m_rendered = true;
		}

		virtual ~ColliderBox() {};
	};
}