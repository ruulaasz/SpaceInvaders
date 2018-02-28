#pragma once
//#include "message.h"
#include "FileManager.h"
#include "World.h"
#include <string>

namespace LCF
{
	template<class _Object, class _type>
	class Factory
	{
	public:
		_Object* create(std::string _name)
		{
			LCF::FileManager::GetInstance().ReadFile(_name.c_str());
			_Object* newObject = new _Object();
			std::string info = LCF::FileManager::GetInstance().GetLine();
			_type* typeObject = new _type();
			typeObject->init(info);
			newObject->setType(typeObject);
			LCF::FileManager::GetInstance().CloseFile();
			return newObject;
		}
		Factory() {};
		virtual ~Factory() {};
	};
}

