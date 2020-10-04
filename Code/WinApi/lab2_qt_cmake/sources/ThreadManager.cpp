#include "stdafx.h"

#include "ThreadManager.h"
#include "SyncManager.h"

#ifdef WIN32
#include "ThreadManagerWinImpl.h"
#else
#error This platform does not supported
#endif

ThreadManager::ThreadManager()
	: m_impl(new ThreadManagerImpl())
	, m_isInitialized(false)
{
}

ThreadManager::~ThreadManager()
{
	delete m_impl;
}

void ThreadManager::Initialize(LogCallbackFactory logCallbackFactory)
{
	if (m_isInitialized || !logCallbackFactory)
	{
		return;
	}
	
	const int threadCount = 2;
	for (int i = 0; i < threadCount; ++i)
	{
		auto logCallback = logCallbackFactory(i);
		if (logCallback)
		{
			auto && data = make_shared<ThreadPrivateData>(logCallback);
			m_privateData.emplace_back(data);
		}
	}

	m_isInitialized = true;
}

void ThreadManager::SetSharedData(ThreadSharedDataPtr data)
{
	if (ThreadsInProcess())
	{
		return;
	}

	m_sharedData = data;
}

void ThreadManager::CreateThreads()
{
	if (!m_isInitialized || ThreadsInProcess())
	{
		return;
	}

	for (auto privateData : m_privateData)
	{
		privateData->needStop.store(false, std::memory_order_release);
		auto threadFunc = CreateThreadFunction(privateData);
		
		m_impl->CreateThread(threadFunc);
	}
}

void ThreadManager::StartThreads()
{
	if (m_isInitialized)
	{
		m_impl->StartThreads();
	}
}

bool ThreadManager::WaitThreads(int milliseconds)
{
	return m_isInitialized && m_impl->WaitThreads(milliseconds);
}

void ThreadManager::StopThreads()
{
	if (m_isInitialized)
	{
		for (auto privateDataPtr : m_privateData)
		{
			privateDataPtr->needStop.store(true, std::memory_order_release);
		}	
	}
}

void ThreadManager::TerminateThreads()
{
	if (m_isInitialized)
	{
		return m_impl->TerminateThreads();	
	}
}

bool ThreadManager::ThreadsInProcess() const
{
	if (m_isInitialized)
	{
		bool workIsDone = m_impl->WaitThreads(0);
		return !workIsDone;	
	}
	return false;
}

void ThreadManager::SetErrorCallback(std::function<void(const string&)> callback)
{
	if (m_isInitialized)
	{
		m_impl->SetErrorCallback(callback);
	}
}

ThreadManager::ThreadFunction ThreadManager::CreateThreadFunction(ThreadPrivateDataPtr data) const
{
	// get raw pointers
	auto privateData = data.get();
	auto sharedData = m_sharedData.get();

	return [privateData, sharedData]()
	{
		if (!privateData || !sharedData)
		{
			return;
		}

		auto sync = sharedData->GetSyncStrategy();
		if (!sync)
		{
			return;
		}

		for (int i = 0; i < 50; ++i)
		{
			if (privateData->needStop.load(std::memory_order_acquire))
			{
				return;
			}

			while (sync->IsLocked())
			{
				sync->Wait();
			}

			sync->Lock();
			int changedData;
			{
				sharedData->IncreaseNumber();
				Sleep(1);
				sharedData->DecreaseNumber();
				changedData = sharedData->GetNumber();
			}
			privateData->logFunction(changedData);
			sync->UnLock();
		}	
	};
}
