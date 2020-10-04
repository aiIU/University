#include "stdafx_lib.h"

#include "utils.h"

#include <Windows.h>
// #include <errhandlingapi.h>
// #include <winbase.h>

namespace utils
{
}

string utils::GetLastErrorMessage(string functionName /* = {} */)
{
	return ErrorCodeToString(::GetLastError(), std::move(functionName));
}

string utils::ErrorCodeToString(int code, string functionName /* = {} */)
{
	void *lpMessageBuffer = nullptr;
	
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		code,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		static_cast<LPSTR>(static_cast<void*>(&lpMessageBuffer)),
		0, nullptr);

	if (!lpMessageBuffer)
	{
		return "";
	}

	auto name = functionName.empty() ? "Function" : functionName;
	auto out = name + " failed with error " + std::to_string(code) + ": " + static_cast<LPCSTR>(lpMessageBuffer);
	out.resize(out.size() - 1);
	LocalFree(lpMessageBuffer);

	return out;
}
