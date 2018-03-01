#include "FileManager.h"

namespace LCF
{
	MESSAGE_LOG FileManager::ReadFile(const char* _fileName)
	{
		if (m_pFile.is_open())
			return MESSAGE_WARNING("It already have a file open");

		m_pFile.open(_fileName, std::ifstream::in);

		if (!m_pFile.is_open())
		{
			return MESSAGE_ERROR("Cant find the file");
		}

		return MESSAGE_SUCCESS("Succes on read File");
	}

	std::string FileManager::GetLine()
	{
		std::string StringLine;
		std::getline(m_pFile, StringLine);
		return StringLine;
	}

	void FileManager::CloseFile()
	{
		m_pFile.close();
	}

	FileManager::FileManager()
	{

	}

	FileManager::~FileManager()
	{

	}
}