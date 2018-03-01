#pragma once

#include "FileManager.h"
#include <map>
#include "Tools.h"

namespace LCF
{
	template<class _Object, class _type>
	class Factory
	{
	public:

		Factory() {};
		virtual ~Factory() {};

		_type* getObject(std::string _name)
		{
			std::map<std::string, _type*>::iterator it;
			it = m_loadedTypes.find(_name);

			if (it != m_loadedTypes.end())
			{
				return it->second;
			}
			else
			{
				return nullptr;
			}
		}

		_Object* create(std::string _name)
		{
			std::string name = getFileName(_name);
			_Object* newObject = new _Object();
			_type* typeObject = new _type();

			typeObject = getObject(name);

			if (typeObject)
			{
				_type* final = new _type(*typeObject);
				newObject->setType(final);
				delete typeObject;
			}
			else
			{
				newObject = new _Object();
				typeObject = new _type();

				LCF::FileManager::GetInstance().ReadFile(_name.c_str());
				std::string info = LCF::FileManager::GetInstance().GetLine();
				LCF::FileManager::GetInstance().CloseFile();

				typeObject->init(info);
				newObject->setType(typeObject);

				m_loadedTypes[name] = typeObject;
			}

			return newObject;
		}

		std::map<std::string, _type*> m_loadedTypes;
	};
}