#include "Include.h"

void DebugString(const char* filePath, int lineNumber, const char* funcName, const char* format, ...)
{
	char str[1024];

	int length = sprintf_s(str, "%s(%d) : %s", filePath, lineNumber, funcName);

	va_list va;
	va_start(va, format);

	vsprintf_s(&str[length], sizeof(str) - length, format, va);

	va_end(va);
	
	OutputDebugString(str);

}