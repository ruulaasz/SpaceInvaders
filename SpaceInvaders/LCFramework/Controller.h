#pragma once
#include <map>
#include "message.h"

namespace LCF
{
	template <class _type, class _struct>
	class Controller
	{
	protected:
		//Member of the functions
		std::map<char, typedef void(_type::*)(_struct)> m_functions;
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
		};
		//function to add functions in the map
		MESSAGE_LOG addFunction(char _input, void(_type::*_foo)(_struct))
		{
			std::pair<std::map<char, void(_type::*)(_struct)>::iterator, bool> ret;
			ret = m_functions.insert(std::pair<char, void(_type::*)(_struct)>(_input, _foo));

			if (!ret.second)
				return MESSAGE_ERROR;

			return MESSAGE_SUCCESS;
		};
		//Checking if this controler have function
		MESSAGE_LOG checkInput(char _input, _struct _info)
		{
			std::map<char, void(_type::*)(_struct)>::iterator it = m_functions.find(_input);

			if (it == m_functions.end())
				return MESSAGE_ERROR;

			(*m_Object.*it->second)(_info);
			return MESSAGE_SUCCESS;
		};
	public:

		Controller() { m_Object = NULL; };
		virtual ~Controller() {};
	};
}

