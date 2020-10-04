#include "stdafx.h"
#include "ProcessManager.h"

#include <cstdio>

HANDLE ProcessManager::CreateProcess(const string & applicationName)
{
	auto commandLine = applicationName;

	STARTUPINFOA sInfo;
	memset(&sInfo, 0, sizeof(sInfo));
	sInfo.cb = sizeof(sInfo);

	PROCESS_INFORMATION pInfo;
	memset(&pInfo, 0, sizeof(pInfo));

	BOOL res = CreateProcessA(nullptr, &commandLine[0], nullptr, nullptr, false, CREATE_BREAKAWAY_FROM_JOB, nullptr,
	                          nullptr, &sInfo, &pInfo);
	if (!res)
	{
		DWORD error = GetLastError();
		throw ProcessException(error, "CreateProcess");
	}

	// Закрываем хендлер созданного _потока_
	CloseHandle(pInfo.hThread);

	DWORD oneTry = 100, secondTry = 1000;
	DWORD result = WaitForInputIdle(pInfo.hProcess, oneTry);
	if (result == WAIT_TIMEOUT)
	{
		result = WaitForInputIdle(pInfo.hProcess, secondTry);
	}

	switch (result)
	{
	case 0:
		break;
	case WAIT_TIMEOUT:
		CloseHandle(pInfo.hProcess);
		throw ProcessException("Waiting timeout");
	case WAIT_FAILED:
	default:
		CloseHandle(pInfo.hProcess);
		throw ProcessException(GetLastError(), "WaitForInputIdle");

	}

	m_processIds.push_back(pInfo.hProcess);

	return pInfo.hProcess;
}

void ProcessManager::TerminateProcess(HANDLE handle)
{
	auto && it = std::find(m_processIds.begin(), m_processIds.end(), handle);
	if (it != m_processIds.end())
	{
		if (!::TerminateProcess(handle, 0))
		{
			throw ProcessException(GetLastError(), "TerminateProcess");
		}
		if (!::CloseHandle(handle))
		{
			throw ProcessException(GetLastError(), "CloseHandle");
		}
		m_processIds.erase(it);
	}
}

ProcessException::ProcessException(string const & error)
	: m_message(error) 
{}

ProcessException::ProcessException(size_t errorCode, string const & functionName)
{
	LPVOID lpMessageBuffer;
	
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMessageBuffer,
		0, nullptr);

	/*
	// Выделяем память
	auto lpDisplayBuffer = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlenA((LPCSTR)lpMessageBuffer) + lstrlenA((LPCSTR)functionName.c_str()) + 40) * sizeof(CHAR));

	std::snprintf((LPSTR)lpDisplayBuffer, LocalSize(lpDisplayBuffer) / sizeof(CHAR), "%s failed with error %d: %s",
		functionName.c_str(), errorCode, lpMessageBuffer);

	m_message = (LPCSTR)lpDisplayBuffer;

	LocalFree(lpDisplayBuffer);
	*/

	m_message = functionName + " failed with error " + std::to_string(errorCode) + ": ";
	m_message += (LPCSTR)lpMessageBuffer;

	LocalFree(lpMessageBuffer);
}
