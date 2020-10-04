#pragma once

class ThreadManagerImpl
{
public:
	~ThreadManagerImpl();

	void CreateThread(const std::function<void()>& userFunction);

	void StartThreads();

	bool WaitThreads(int waitingTime);

	void TerminateThreads();

	void SetErrorCallback(std::function<void(const string &)> callback);

	void LogLastError(const string & functionName) const;

	void EchoErrorMessage(const string & error) const;
	
private:
	struct WinFunc
	{
		LPTHREAD_START_ROUTINE		startFunc;
		LPVOID						paramsPtr;
	};

	vector<WinFunc>			m_threadFunctions;
	vector<HANDLE>							m_threadHandles;
	std::function<void(const string &)>		m_errorCallback;
};