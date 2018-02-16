#pragma once
#include <map>
#include "message.h"
#include "SDL_Manager.h"

namespace LCF
{
	class BaseController
	{
	public:
		virtual MESSAGE_LOG checkInput(char _input) { return MESSAGE_SUCCESS; };
	public:
		BaseController() {};
		virtual ~BaseController() {};

	};

	template <class _type, class _struct>
	class Controller : public BaseController
	{
	protected:
		//Member of the functions
		std::map<char, typedef void(_type::*)(_struct)> m_functions;
		//Member of all values
		std::map<char, _struct*> m_values;
		//pointer to de class
		_type* m_Object;
	public:
		//Add the object
		MESSAGE_LOG addObject(_type* _object)
		{
			if (_object == NULL)
				return MESSAGE_ERROR;
			if (m_Object != NULL)
				return MESSAGE_ERROR;

			m_Object = _object;
			return MESSAGE_SUCCESS;
		}
		//function to add functions in the map
		MESSAGE_LOG addFunctionAndValues(char _input, void(_type::*_foo)(_struct), _struct* _value)
		{
			if (_value == NULL)
				return MESSAGE_ERROR;

			std::pair<std::map<char, void(_type::*)(_struct)>::iterator, bool> ret;
			ret = m_functions.insert(std::pair<char, void(_type::*)(_struct)>(_input, _foo));

			if (!ret.second)
			{
				delete _value;
				return MESSAGE_ERROR;
			}
			m_values.insert(std::pair<char, _struct*>(_input, _value));
			return MESSAGE_SUCCESS;
		}
		//Checking if this controler have function
		virtual MESSAGE_LOG checkInput(char _input)
		{
			std::map<char, void(_type::*)(_struct)>::iterator it = m_functions.find(_input);

			if (it == m_functions.end())
				return MESSAGE_ERROR;

			(*m_Object.*it->second)(*m_values[_input]);
			return MESSAGE_SUCCESS;
		}
		void DestroyController()
		{
			for each (std::map<char, _struct*>::iterator it in m_values)
			{
				delete it->second;
			}
		}
	public:

		Controller() { m_Object = NULL; };
		virtual ~Controller() {};
	};
}

