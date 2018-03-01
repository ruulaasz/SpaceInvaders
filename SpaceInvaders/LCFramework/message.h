#pragma once
#include <iostream>

#define MESSAGE_LOG char*
#define M_ERROR "ERROR"
#define M_SUCCESS "SUCCESS"
#define M_WARNING "WARNING"

#ifdef _DEBUG


static bool PrinteMessage = false;
static inline MESSAGE_LOG ReturnCallMessage(MESSAGE_LOG Descriptor, MESSAGE_LOG aditionalText, int line, char* foo, char* file)
{
	if(PrinteMessage)
		std::cout << "\n" <<line << "::" << foo << "::" << file << "::" << Descriptor << "::" << aditionalText << ".\n";
	return Descriptor;
}

#define ENABLE_PRINT_MESSAGE(value) PrinteMessage = value 
#define PPRINT_MESSAGE(Descriptor, aditionalText, line, foo, file) ReturnCallMessage(Descriptor, aditionalText, line, foo, file)
#define MESSAGE_ERROR(Text) PPRINT_MESSAGE(M_ERROR , Text, __LINE__, __FUNCTION__, __FILE__)
#define MESSAGE_SUCCESS(Text) PPRINT_MESSAGE(M_SUCCESS, Text, __LINE__, __FUNCTION__, __FILE__)
#define MESSAGE_WARNING(Text) PPRINT_MESSAGE(M_WARNING, Text, __LINE__, __FUNCTION__, __FILE__)
#else
#define ENABLE_PRINT_MESSAGE(...)
#define PPRINT_MESSAGE(...) 
#define MESSAGE_ERROR(...) M_ERROR
#define MESSAGE_SUCCESS(...) M_SUCCESS
#define MESSAGE_WARNING(...) M_WARNING

static MESSAGE_LOG ReturnCallMessage(MESSAGE_LOG Descriptor, MESSAGE_LOG aditionalText, int line, char* foo, char* file)
{
	return Descriptor;
}
#endif// !_DEBUG
