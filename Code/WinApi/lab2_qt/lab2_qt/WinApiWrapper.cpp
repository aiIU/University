#include "stdafx.h"
#include "WinApiWrapper.h"

string WinApiWrapper::ErrorCodeToString(DWORD code, const string& functionName)
{
	LPVOID lpMessageBuffer = nullptr;
	
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMessageBuffer,
		0, nullptr);

	if (!lpMessageBuffer)
	{
		return "";
	}

	auto name = functionName.empty() ? "Function" : functionName;
	auto out = name + " failed with error " + std::to_string(code) + ": " + (LPCSTR)lpMessageBuffer;
	LocalFree(lpMessageBuffer);

	return out;
}
