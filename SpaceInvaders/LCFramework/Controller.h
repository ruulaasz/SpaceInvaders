#pragma once
#include <map>
#include "message.h"
#include "SDL_Manager.h"

namespace LCF
{
	class BaseController
	{
	public:
		virtual MESSAGE_LOG checkInput(char _input, Uint32 _typeEvent) { return MESSAGE_SUCCESS("Checking Input"); };
	public:
		BaseController() {};
		virtual ~BaseController() {};

	};
	
	template <class _type, class _struct>
	class Controller : public BaseController
	{
	public:
#define FunctionPair std::pair<char, void(_type::*)(_struct)> 
#define FunctionIterator std::map<char, void(_type::*)(_struct)>::iterator
#define FunctionMap std::map<char, void(_type::*)(_struct)> 
#define StructPair std::pair<char, _struct*>
#define StructIterator std::map<char, _struct*>::iterator 
#define StructMap std::map<char, _struct*> 
#define TypeEventPair std::pair<char, Uint32> 
#define TypeEventIterator std::map<char, Uint32>::iterator 
#define TypeEventMap std::map<char, Uint32> 
	protected:
		//Member of the functions
		FunctionMap m_functions;
		//Member of all values
		StructMap m_values;
		//Member whit all type of eventes
		TypeEventMap m_typeEvents;
		//pointer to de class
		_type* m_Object;
	public:
		//Add the object
		MESSAGE_LOG addObject(_type* _object)
		{
			if (_object == NULL)
				return MESSAGE_ERROR("The object is NULL");

			if (m_Object != NULL)
				return MESSAGE_ERROR("The controller already had a objet");
			

			m_Object = _object;
			return MESSAGE_SUCCESS("to add");
		}
		//function to add functions in the map
		MESSAGE_LOG addFunctionAndValues(char _input, Uint32 _typeEvent, void(_type::*_foo)(_struct), _struct* _value)
		{
			if (_value == NULL)
			{
				return MESSAGE_ERROR("The pointer of the value is NULL");
			}
			std::pair<FunctionIterator, bool> ret;
			ret = m_functions.insert(FunctionPair(_input, _foo));

			if (!ret.second)
			{
				delete _value;
				return MESSAGE_ERROR("the functions is alredy added");
			}
			m_typeEvents.insert(TypeEventPair(_input, _typeEvent));
			m_values.insert(StructPair(_input, _value));
			return MESSAGE_SUCCESS("Succes to add");
		}
		//Checking if this controler have function
		virtual MESSAGE_LOG checkInput(char _input, Uint32 _typeEvent)
		{
			ENABLE_PRINT_MESSAGE(false);
			FunctionIterator it = m_functions.find(_input);

			if (it == m_functions.end())
			{
				return MESSAGE_WARNING("Cant find the input in the map");
			}

			TypeEventIterator itEvent = m_typeEvents.find(_input);

			if (itEvent == m_typeEvents.end())
			{
				return MESSAGE_WARNING("Cant find the input in the map");
			}

			if (itEvent->second == _typeEvent)
				(*m_Object.*it->second)(*m_values[_input]);
			else
			{
				return MESSAGE_WARNING("The type event is different");
			}
			
			return MESSAGE_SUCCESS("The input is correct and event type");

			ENABLE_PRINT_MESSAGE(true);
		}
		void DestroyController()
		{
			for each (std::map<char, _struct*>::iterator it in m_values)
			{
				delete it->second;
			}
			m_values.clear();
			m_typeEvents.clear();
			m_functions.clear();
			m_Object = NULL;
		}
	public:

		Controller() { m_Object = NULL; };
		virtual ~Controller() {};
	};
}

