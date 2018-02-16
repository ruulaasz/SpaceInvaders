#pragma once
#include <string>

namespace LCF
{
	/**
	* A container class for an Asset
	*/
	class Asset
	{
	public:
		Asset();
		virtual ~Asset();

	public:
		std::string m_name;
	};
}