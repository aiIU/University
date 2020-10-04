#pragma once

#include "pch.h"

#include <Windows.h>
#undef CreateProcess
#undef max

class ProcessException : public exception
{
public:
	ProcessException(string const & error);
	ProcessException(size_t code, string const & functionName);

	const char * what() const noexcept override { return m_message.c_str(); }

private:
	string m_message;
};

class ProcessManager
{
public:
	HANDLE CreateProcess(const string & applicationName);

	auto & GetOpenProcesses() const { return m_processIds; }

	void TerminateProcess(HANDLE handle);

private:
	vector<HANDLE> m_processIds;
};