#pragma once

#include <Windows.h>
#undef CreateProcess
#undef max

class ProcessException : public exception
{
public:
	ProcessException(string const & error);
	ProcessException(int errorCode, string const & functionName);

	const char * what() const noexcept override { return m_message.c_str(); }

private:
	string m_message;
};

class ProcessManager
{
public:
	HANDLE CreateProcess(const string & applicationName);

	vector<HANDLE> GetOpenProcesses() const { return m_processIds; }

	void TerminateProcess(HANDLE handle);

private:
	vector<HANDLE> m_processIds;
};