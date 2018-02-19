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

		std::string getName() { return m_name; }
		void setName(std::string _name) { m_name = _name; }

	private:
		std::string m_name;
	};
}