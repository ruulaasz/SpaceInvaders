#pragma once

template<class _type>
class Module
{
protected:
	static _type*& instance() {
		static _type* inst = NULL;
		return inst;
	}
	
public:
	static void StartModule() 
	{
		instance() = new _type();
	}
	static _type& GetInstance()
	{
		return *instance();
	}
	static _type* GetPointerInstance()
	{
		return instance();
	}
	static void CloseModule()
	{
		delete instance();
		instance() = NULL;
	}
public:
	Module(){}
	virtual ~Module(){}
};