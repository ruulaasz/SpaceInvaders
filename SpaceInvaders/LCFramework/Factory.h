#pragma once
//#include "message.h"
#include "FileManager.h"
#include "World.h"
namespace LCF
{
	template<class _Object, class _type>
	class Factory
	{
	public:
		_Object* create(std::string _name)
		{
			LCF::FileManager::GetInstance().ReadFile(name);
			_Object* newObject = new _Object();
			std::string fi = LCF::FileManager::GetInstance().GetLine();
			_type typeObject;
			typeObject.Init(fi);
			newObject->SetType(typeObject);
			LCF::FileManager::CloseFile();
			return newObject;
		}
		Factory() {};
		virtual ~Factory() {};
	};
}

