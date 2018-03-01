#pragma once

#include<fstream>
#include <string>
#include "Module.h"
#include "message.h"

namespace LCF
{
	class FileManager : public Module<FileManager> 
	{
	protected:
		std::ifstream m_pFile;

	public:
		MESSAGE_LOG ReadFile(const char* _fileName);
		std::string GetLine();
		void CloseFile();
		FileManager();
		~FileManager();
	};
}