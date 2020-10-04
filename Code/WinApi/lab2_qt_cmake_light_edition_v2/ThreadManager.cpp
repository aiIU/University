#include "stdafx.h"
#include "ThreadManager.h"

ThreadManager::ThreadManager()
	: m_threadCommonData(nullptr)
	, m_semaphore(nullptr)
	, m_mutex(nullptr)
	, m_event(nullptr)
	, m_isInitialized(false)
	, m_isConfigurated(false)
{
	std::memset(&m_critSection, 0, sizeof(CRITICAL_SECTION));
}

ThreadManager::~ThreadManager()
{
	if (m_isConfigurated)
	{
		if (ThreadsInProcess())
		{
			ForceStopThreads();
		}
		Reset();
	}

	// Удаляем объекты синхронизации
	DeleteCriticalSection(&m_critSection);
	ReleaseMutex(m_mutex);
	CloseHandle(m_mutex);
	CloseHandle(m_event);
	CloseHandle(m_semaphore);
}

void ThreadManager::Initialize(const LogCallback& left, const LogCallback& right)
{
	if (m_isInitialized)
	{
		return;
	}
	m_isInitialized = true;
	
	// Создаём объекты синхронизации
	InitializeCriticalSection(&m_critSection);
	m_mutex = CreateMutexA(nullptr, false, nullptr);
	m_event = CreateEventA(nullptr, true, true, nullptr);
	m_semaphore = CreateSemaphoreA(nullptr, 1, 1, nullptr);
	
	m_callbackLeft = left;
	m_callbackRight = right;
}

void ThreadManager::Configurate(int delta, SyncType type)
{
	if (!m_isInitialized)
	{
		return;
	}

	if (m_isConfigurated)
	{
		Reset();
	}
	m_isConfigurated = true;
	
	m_threadLeft.params = new ThreadParams();
	m_threadRight.params = new ThreadParams();

	void *ptr = nullptr;
	switch (type)
	{
	case SyncType::CRITICAL_SECTION:
		ptr = &m_critSection;
		break;
	case SyncType::EVENT:
		ptr = m_event;
		break;
	case SyncType::MUTEX:
		ptr = m_mutex;
		break;
	case SyncType::SEMAPHORE:
		ptr = m_semaphore;
		break;
	default:
		ptr = nullptr;
		break;
	}

	auto commonData = new ThreadCommonData(0, delta);
	m_threadLeft.params->Initialize(commonData, type, ptr, m_callbackLeft);
	m_threadRight.params->Initialize(commonData, type, ptr, m_callbackRight);
	m_threadCommonData = commonData;
}

void ThreadManager::Reset()
{
	if (ThreadsInProcess() || !m_isConfigurated)
	{
		return;
	}

	m_isConfigurated = false;

	delete m_threadLeft.params;
	m_threadLeft.params = nullptr;

	delete m_threadRight.params;
	m_threadRight.params = nullptr;

	delete m_threadCommonData;
	m_threadCommonData = nullptr;

	CloseHandle(m_threadLeft.handle);	
	m_threadLeft.handle = nullptr;

	CloseHandle(m_threadRight.handle);
	m_threadRight.handle = nullptr;
}

void ThreadManager::StartThreads()
{
	if (ThreadsInProcess())
	{
		return;
	}
	
	void* params = static_cast<void*>(m_threadLeft.params);
	m_threadLeft.handle = CreateThread(nullptr, 0, &ThreadManager::ThreadFunction, params, 0, nullptr);

	params = static_cast<void*>(m_threadRight.params);
	m_threadRight.handle = CreateThread(nullptr, 0, &ThreadManager::ThreadFunction, params, 0, nullptr);
}

bool ThreadManager::WaitThreads(int millisec) const
{
	bool isCompleted = true;
	if (m_isConfigurated && m_threadLeft.handle && m_threadRight.handle)
	{
		auto res1 = WaitForSingleObject(m_threadLeft.handle, millisec);
		auto res2 = WaitForSingleObject(m_threadRight.handle, millisec);
		return res1 == WAIT_OBJECT_0 && res2 == WAIT_OBJECT_0;
	}
	return isCompleted;
}

void ThreadManager::ForceStopThreads()
{
	if (ThreadsInProcess())
	{
		TerminateThread(m_threadLeft.handle, 1);
		TerminateThread(m_threadRight.handle, 1);

		Reset();
	}
}

void ThreadManager::TryStopThreads()
{
	if (ThreadsInProcess())
	{
		m_threadCommonData->SetForseStop();
		(void)WaitThreads(1000);
		Reset();
	}
}

DWORD ThreadManager::ThreadFunction(LPVOID wrappedParams)
{
	ThreadParams * params = static_cast<ThreadParams*>(wrappedParams);
	for (int i = 0; i < 101; ++i)
	{
		if (params->GetData()->NeedForseStop())
		{
			break;
		}
		while(params->IsLocked())
		{
			params->Wait();
		}
		params->Lock();
		{
			params->GetData()->IncreaseNumber();
			Sleep(1);
			params->GetData()->DecreaseNumber();
		}
		params->DoLogData();
		params->Unlock();
	}
	return 0;
}

ThreadParams::ThreadParams()
	: m_data(nullptr)
	, m_syncType(SyncType::NO_SYNCHRONIZATION)
	, m_critSection(nullptr)
	, m_handle(nullptr)
	, m_isInitialized(false)
{
}

void ThreadParams::Initialize(ThreadCommonData *data, SyncType type, void* handle, const LogCallback& callback)
{
	if (m_isInitialized)
	{
		return;
	}
	m_isInitialized = true;

	m_data = data;

	m_syncType = type;
	if (type == SyncType::CRITICAL_SECTION)
	{
		m_critSection = static_cast<LPCRITICAL_SECTION>(handle);
	}
	else
	{
		m_handle = static_cast<HANDLE>(handle);
	}

	m_logCallback = callback;
}

void ThreadParams::Lock()
{
	if (!m_isInitialized)
	{
		return;
	}

	switch (m_syncType)
	{
	case SyncType::CRITICAL_SECTION:
		EnterCriticalSection(m_critSection);
		break;
	case SyncType::MUTEX:
		// nothing to do
		break;
	case SyncType::EVENT:
		ResetEvent(m_handle);
		break;
	case SyncType::SEMAPHORE:
		WaitForSingleObject(m_handle, INFINITE);	
		break;
	default:
		break;
	}
}

void ThreadParams::Unlock()
{
	if (!m_isInitialized)
	{
		return;
	}

	switch (m_syncType)
	{
	case SyncType::CRITICAL_SECTION:
		LeaveCriticalSection(m_critSection);
		break;
	case SyncType::MUTEX:
		ReleaseMutex(m_handle);
		break;
	case SyncType::EVENT:
		SetEvent(m_handle);
		break;
	case SyncType::SEMAPHORE:
		ReleaseSemaphore(m_handle, 1, nullptr);
		break;
	default:
		break;
	}
}

void ThreadParams::Wait()
{
	if (!m_isInitialized)
	{
		return;
	}

	switch (m_syncType)
	{
	case SyncType::CRITICAL_SECTION:
		break;
	case SyncType::MUTEX:
		WaitForSingleObject(m_handle, INFINITE);
		break;
	case SyncType::EVENT:
		WaitForSingleObject(m_handle, INFINITE);
		break;
	case SyncType::SEMAPHORE:	
		break;
	default:
		break;
	}
}

bool ThreadParams::IsLocked()
{	 
	if (!m_isInitialized)
	{
		return false;
	}

	switch (m_syncType)
	{
	case SyncType::CRITICAL_SECTION:
		break;
	case SyncType::MUTEX:
		return WaitForSingleObject(m_handle, 0) != WAIT_OBJECT_0;
	case SyncType::EVENT:
		return WaitForSingleObject(m_handle, 0) != WAIT_OBJECT_0;
	case SyncType::SEMAPHORE:
		break;
	default:
		break;
	}
	return false;
}

void ThreadParams::DoLogData()
{
	if (m_logCallback && m_data)
	{
		m_logCallback(m_data->GetNumber());
	}
}
