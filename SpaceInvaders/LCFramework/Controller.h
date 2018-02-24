#pragma once
#include <vector>
#include "message.h"
#include "SDL_Manager.h"

namespace LCF
{
	class BaseController
	{
	public:
		virtual inline MESSAGE_LOG checkInput(int /*_input*/ = 0, Uint32 /*_typeEvent*/ = 0) { return MESSAGE_SUCCESS("Checking Input"); };
	public:
		BaseController() {};
		virtual ~BaseController() {};

	};

	template <class _type, class _struct>
	class Controller : public BaseController
	{
	public: 
		struct BasicInformation
		{
			int Cinput;
			void(_type::*PFunction)(_struct);
			_struct* Svalue;
			Uint32 UtypeEvent;

		};
#define BIIterator std::vector<BasicInformation*>::iterator
#define BIVector std::vector<BasicInformation*> 
	protected:
		//Member of the functions
		BIVector m_BasicInformations;
		//pointer to de class
		_type* m_Object;
	public:
		//Add the object
		inline MESSAGE_LOG addObject(_type* _object)
		{
			if (_object == NULL)
				return MESSAGE_ERROR("The object is NULL");

			if (m_Object != NULL)
				return MESSAGE_ERROR("The controller already had a objet");
			

			m_Object = _object;
			return MESSAGE_SUCCESS("to add");
		}
		//function to add functions in the map
		inline MESSAGE_LOG addFunctionAndValues(int _input, Uint32 _typeEvent, void(_type::*_foo)(_struct), _struct* _value)
		{
			if (_value == NULL)
			{
				return MESSAGE_ERROR("The pointer of the value is NULL");
			}

			if (_foo == NULL)
			{
				return MESSAGE_ERROR("The pointer of the function is NULL");
			}

			if (std::string(M_WARNING) == std::string(CheckForExistInput(_input, _typeEvent)))
			{
				return MESSAGE_WARNING("That input already exist");
			}

			BasicInformation* addToVector = new BasicInformation();
			addToVector->Cinput = _input;
			addToVector->PFunction = _foo;
			addToVector->Svalue = _value;
			addToVector->UtypeEvent = _typeEvent;

			m_BasicInformations.push_back(addToVector);
			return MESSAGE_SUCCESS("Succes to add");
		}
		//Checking if this controler have function
		virtual inline MESSAGE_LOG checkInput(int _input, Uint32 _typeEvent)
		{
			ENABLE_PRINT_MESSAGE(false);
			for (size_t i = 0; i < m_BasicInformations.size(); i++)
			{
				BasicInformation* _BI = m_BasicInformations[i];
				if (_BI->Cinput == _input && _BI->UtypeEvent == _typeEvent)
				{
					(*m_Object.*_BI->PFunction)(*_BI->Svalue);
					return MESSAGE_SUCCESS("The input is correct and event type");
				}
			}

			return MESSAGE_WARNING("Error to find The input and the type event");
		}
		inline MESSAGE_LOG CheckForExistInput(int _input, Uint32 _typeEvent)
		{
			for (size_t i = 0; i < m_BasicInformations.size(); i++)
			{
				if (m_BasicInformations[i]->Cinput == _input && m_BasicInformations[i]->UtypeEvent == _typeEvent)
				{
					return MESSAGE_WARNING("That input its already exist");
				}
			}
			return MESSAGE_SUCCESS("That input dont Exist");
		}
		inline void DestroyController()
		{
			for (size_t i = 0; i < m_BasicInformations.size(); i++)
			{
				delete m_BasicInformations[i].Svalue;
				delete m_BasicInformations[i];
			}
			m_BasicInformations.clear();
			m_Object = NULL;
		}
	public:

		Controller() { m_Object = NULL; };
		virtual ~Controller() {};
	};
}

