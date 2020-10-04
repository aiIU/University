#include "stdafx.h"

#include "ThreadManager.h"
#include "SyncApi.h"
#include "WinApiWrapper.h"

class ThreadManager::ThreadManagerImpl
{
public:
	void CreateThread(std::function<void()> func)
	{
		auto winFuncWrapper = [](LPVOID params) -> DWORD
		{
			auto funcPtr = static_cast<std::function<void()>*>(params);
			if (funcPtr)
			{
				auto func = *funcPtr;
				func();	
			}
			delete funcPtr;
			return 0;
		};

		auto funcPtr = new std::function<void()>(func);
		auto params = static_cast<LPVOID>(funcPtr);
		auto handle = ::CreateThread(nullptr, 0, winFuncWrapper, params, CREATE_SUSPENDED, nullptr);
		m_threadHandles.push_back(handle);
	}

	void StartThreads()
	{
		for (auto handle : m_threadHandles)
		{
			ResumeThread(handle);
		}
	}

	bool WaitThreads(int milliseconds)
	{
		bool ready = true;

		for (auto it = m_threadHandles.begin(); it != m_threadHandles.end();)
		{
			auto handle = *it;
			auto res = WaitForSingleObject(handle, milliseconds);

			if (res == WAIT_OBJECT_0 || res == WAIT_ABANDONED)
			{
				CloseHandle(handle);
				it = m_threadHandles.erase(it);
			}
			else
			{
				ready = false;
				if (res == WAIT_FAILED)
				{
					LogLastError("WaitForSingleObject");
				}
				++it;
			}
		}
		return ready;
	}

	void TerminateThreads()
	{
		for (auto handle : m_threadHandles)
		{
			bool success = ::TerminateThread(handle, 1);
			if (!success)
			{
				LogLastError("TerminateThread");
			}
			else
			{
				EchoErrorMessage("Thread was terminated forcibly!");
			}

			success = ::CloseHandle(handle);
			if (!success)
			{
				LogLastError("CloseHandle");
			}
		}
		m_threadHandles.clear();
	}

	void SetErrorCallback(std::function<void(const string &)> callback)
	{
		m_errorCallback = callback;
	}

	void LogLastError(const string & functionName) const
	{
		if (m_errorCallback)
		{
			auto message = WinApiWrapper::ErrorCodeToString(GetLastError(), functionName);
			m_errorCallback(message);	
		}
	}

	void EchoErrorMessage(const string & error) const
	{
		if (m_errorCallback)
		{
			m_errorCallback(error);
		}
	}
	
private:
	vector<HANDLE>							m_threadHandles;
	std::function<void(const string &)>		m_errorCallback;
};


ThreadManager::ThreadManager()
	: m_impl(new ThreadManagerImpl())
{
}

ThreadManager::~ThreadManager()
{
	delete m_impl;
}

void ThreadManager::CreateThreads(std::function<LogFunction(int)> logCreator, shared_ptr<ThreadData> threadData, int threadCount)
{
	for (int i = 0; i < threadCount; ++i)
	{
		LogFunction logger = logCreator(i);
		ThreadFunction mainFunction = CreateThreadFunction(logger, threadData);
		CreateThread(mainFunction);
	}
}

void ThreadManager::CreateThread(std::function<void()> func)
{
	m_impl->CreateThread(func);
}

void ThreadManager::StartThreads()
{
	m_impl->StartThreads();
}

bool ThreadManager::WaitThreads(int milliseconds)
{
	return m_impl->WaitThreads(milliseconds);
}

void ThreadManager::TerminateThreads()
{
	return m_impl->TerminateThreads();
}

bool ThreadManager::ThreadsInProcess() const
{
	bool workIsDone = m_impl->WaitThreads(0);
	return !workIsDone;
}

void ThreadManager::SetErrorCallback(std::function<void(const string&)> callback)
{
	m_impl->SetErrorCallback(callback);
}

ThreadManager::ThreadFunction ThreadManager::CreateThreadFunction(LogFunction logger, shared_ptr<ThreadData> threadData) const
{
	weak_ptr<ThreadData> weakData = threadData;
	return [logger, weakData]()
		{
			auto threadData = weakData.lock();
			if (!threadData)
			{
				return;
			}
			auto sync = threadData->m_sync.lock();

			for (int i = 0; i < 50; ++i)
			{
				if (threadData->m_forceStop.load(std::memory_order_acquire))
				{
					break;
				}
				
				if (sync)
				{
					while (sync->IsLocked())
					{
						sync->Wait();
					}	
					sync->Lock();
				}

				threadData->m_data += threadData->m_delta;
				Sleep(1);
				threadData->m_data -= threadData->m_delta;
				int changedData = threadData->m_data;

				if (sync)
				{
					sync->UnLock();	
				}

				logger(changedData);
			}	
		};
}
