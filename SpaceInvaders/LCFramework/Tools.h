#pragma once
#include <string>
#include <algorithm>

namespace LCF
{
	static std::string getFileName(std::string _route)
	{
		std::string name;

		int i = _route.length();
		i--;

		for (i; i >= 0; i--)
		{
			if (_route.at(i) == 92)
			{
				break;
			}

			name.push_back(_route.at(i));
		}

		std::reverse(name.begin(), name.end());

		for (size_t i = 0; i < 4; i++)
		{
			name.pop_back();
		}

		return name;
	}
}