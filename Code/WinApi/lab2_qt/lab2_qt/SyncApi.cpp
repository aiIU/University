#include "stdafx.h"
#include "SyncApi.h"
#include "WinApiWrapper.h"


class NoSyncStrategy final : public ISyncStrategy
{
public:
	void Lock() override {}
	void UnLock() override {}
	bool IsLocked() override { return false; }
	void Wait() override {}
};


class CriticalSectionStrategy final : public ISyncStrategy
{
public:
	void Initialize(LPCRITICAL_SECTION critical)
	{
		m_critical = critical;
	}

	void Lock() override
	{
		EnterCriticalSection(m_critical);	
	}

	void UnLock() override
	{
		LeaveCriticalSection(m_critical);
	}

	bool IsLocked() override
	{
		return false;
	}

	void Wait() override {}

private:
	LPCRITICAL_SECTION		m_critical = nullptr;
};


class MutexStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE mutex)
	{
		m_mutex = mutex;
	}
	
	void Lock() override {}

	void UnLock() override
	{
		ReleaseMutex(m_mutex);
	}

	bool IsLocked() override
	{
		return WaitForSingleObject(m_mutex, 0) != WAIT_OBJECT_0;
	}

	void Wait() override
	{
		WaitForSingleObject(m_mutex, INFINITE);
	}

private:
	HANDLE		m_mutex = nullptr;
};


class EventStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE event)
	{
		m_event = event;
	}
	
	void Lock() override
	{
		ResetEvent(m_event);
	}

	void UnLock() override
	{
		SetEvent(m_event);
	}

	bool IsLocked() override
	{
		return WaitForSingleObject(m_event, 0) != WAIT_OBJECT_0;
	}

	void Wait() override
	{
		WaitForSingleObject(m_event, INFINITE);
	}

private:
	HANDLE		m_event = nullptr;
};

class SemaphoreStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE semaphore)
	{
		m_semaphore = semaphore;
	}

	void Lock() override
	{
		WaitForSingleObject(m_semaphore, INFINITE);	
	}

	void UnLock() override
	{
		ReleaseSemaphore(m_semaphore, 1, nullptr);	
	}

	bool IsLocked() override { return false; }
	void Wait() override {}

private:
	HANDLE		m_semaphore = nullptr;
};

class WaitableTimerStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE timer)
	{
		m_timer = timer;
	}

	void Lock() override
	{
		SetWaitableTimer(m_timer, nullptr, 100, nullptr, nullptr, true);
	}

	void UnLock() override
	{
	}

	bool IsLocked() override
	{
		auto res = WaitForSingleObject(m_timer, 0);
		return res == WAIT_TIMEOUT;
	}

	void Wait() override
	{
		WaitForSingleObject(m_timer, INFINITE);
	}

private:
	HANDLE m_timer = nullptr;
};


class SyncManager::SyncManagerImpl
{
public:
	SyncManagerImpl()
		: m_mutex(nullptr)
		, m_event(nullptr)
		, m_semaphore(nullptr)
		, m_timer(nullptr)
	{
		std::memset(&m_critical, 0, sizeof(CRITICAL_SECTION));
	}
	~SyncManagerImpl()
	{
		if (m_criticalStrategy)
		{
			if (m_criticalStrategy.use_count() > 1)
			{
				EchoErrorMessage("Critical section was deleted, when used by someone else.");
			}
			DeleteCriticalSection(&m_critical);
		}

		if (m_mutexStrategy)
		{
			if (m_mutexStrategy.use_count() > 1)
			{
				EchoErrorMessage("Mutex was closed, when used by someone else.");
			}
			if (!CloseHandle(m_mutex))
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CloseHandle");
				EchoErrorMessage(msg);
			}
		}

		if (m_eventStrategy)
		{
			if (m_eventStrategy.use_count() > 1)
			{
				EchoErrorMessage("Event was closed, when used by someone else.");
			}
			if (!CloseHandle(m_event))
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CloseHandle");
				EchoErrorMessage(msg);
			}
		}

		if (m_semaphoreStrategy)
		{
			if (m_semaphoreStrategy.use_count() > 1)
			{
				EchoErrorMessage("Semaphore was closed, when used by someone else.");
			}
			if (!CloseHandle(m_semaphore))
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CloseHandle");
				EchoErrorMessage(msg);
			}
		}

		if (m_timerStrategy)
		{
			if (m_timerStrategy.use_count() > 1)
			{
				EchoErrorMessage("Timer was closed, when used by someone else.");
			}
			if (!CloseHandle(m_timer))
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CloseHandle");
				EchoErrorMessage(msg);
			}
		}
	}

	void SetErrorCallback(std::function<void(const string &)> callback)
	{
		m_errorCallback = callback;	
	}

	shared_ptr<ISyncStrategy> CreateNoSyncStrategy()
	{
		if (!m_noSyncStrategy)
		{
			m_noSyncStrategy = make_shared<NoSyncStrategy>();
		}
		return m_noSyncStrategy;
	}

	shared_ptr<ISyncStrategy> CreateCriticalSectionStrategy()
	{
		if (!m_criticalStrategy)
		{
			m_criticalStrategy = make_shared<CriticalSectionStrategy>();
			InitializeCriticalSection(&m_critical);
			m_criticalStrategy->Initialize(&m_critical);
		}
		return m_criticalStrategy;
	}

	shared_ptr<ISyncStrategy> CreateMutexStrategy()
	{
		if (!m_mutexStrategy)
		{
			m_mutex = CreateMutexA(nullptr, false, nullptr);
			if (!m_mutex)
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CreateMutex");
				EchoErrorMessage(msg);
				return nullptr;
			}
			m_mutexStrategy = make_shared<MutexStrategy>();
			m_mutexStrategy->Initialize(m_mutex);
		}
		return m_mutexStrategy;
	}

	shared_ptr<ISyncStrategy> CreateEventStrategy()
	{
		if (!m_eventStrategy)
		{
			m_event = CreateEventA(nullptr, true, true, nullptr);
			if (!m_event)
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CreateEvent");
				EchoErrorMessage(msg);
				return nullptr;
			}
			m_eventStrategy = make_shared<EventStrategy>();
			m_eventStrategy->Initialize(m_event);

		}
		return m_eventStrategy;
	}

	shared_ptr<ISyncStrategy> CreateSemaphoreStrategy()
	{
		if (!m_semaphoreStrategy)
		{
			m_semaphore = CreateSemaphoreA(nullptr, 1, 1, nullptr);
			if (!m_semaphore)
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CreateSemaphore");
				EchoErrorMessage(msg);
				return nullptr;
			}
			m_semaphoreStrategy = make_shared<SemaphoreStrategy>();
			m_semaphoreStrategy->Initialize(m_semaphore);
		}
		return m_semaphoreStrategy;
	}

	shared_ptr<ISyncStrategy> CreateTimerStrategy()
	{
		if (!m_semaphoreStrategy)
		{
			m_timer = CreateWaitableTimerA(nullptr, TRUE, nullptr);
			if (!m_timer)
			{
				auto msg = WinApiWrapper::ErrorCodeToString(GetLastError(), "CreateWaitableTimer");
				EchoErrorMessage(msg);
				return nullptr;
			}
			m_timerStrategy = make_shared<WaitableTimerStrategy>();
			m_timerStrategy->Initialize(m_timer);
		}
		return m_timerStrategy;
	}

private:
	void EchoErrorMessage(const string &error) const
	{
		if (m_errorCallback)
		{
			m_errorCallback(error);
		}
	}

	CRITICAL_SECTION						m_critical;
	HANDLE									m_mutex;
	HANDLE									m_event;
	HANDLE									m_semaphore;
	HANDLE									m_timer;

	shared_ptr<NoSyncStrategy>				m_noSyncStrategy;
	shared_ptr<CriticalSectionStrategy>		m_criticalStrategy;
	shared_ptr<MutexStrategy>				m_mutexStrategy;
	shared_ptr<EventStrategy>				m_eventStrategy;
	shared_ptr<SemaphoreStrategy>			m_semaphoreStrategy;
	shared_ptr<WaitableTimerStrategy>		m_timerStrategy;

	std::function<void(const string &)>		m_errorCallback;
};

SyncManager::SyncManager()
	: m_impl(new SyncManagerImpl)
{
}

SyncManager::~SyncManager()
{
	delete m_impl;
}

shared_ptr<ISyncStrategy> SyncManager::GetNoSyncStrategy()
{
	return m_impl->CreateNoSyncStrategy();
}

shared_ptr<ISyncStrategy> SyncManager::GetCriticalSectionStrategy()
{
	return m_impl->CreateCriticalSectionStrategy();
}

shared_ptr<ISyncStrategy> SyncManager::GetTimerStrategy()
{
	return m_impl->CreateTimerStrategy();
}

shared_ptr<ISyncStrategy> SyncManager::GetSemaphoreStrategy()
{
	return m_impl->CreateSemaphoreStrategy();
}

shared_ptr<ISyncStrategy> SyncManager::GetMutexStrategy()
{
	return m_impl->CreateMutexStrategy();
}

shared_ptr<ISyncStrategy> SyncManager::GetEventStrategy()
{
	return m_impl->CreateEventStrategy();
}

void SyncManager::SetErrorCallback(std::function<void(const string&)> callback)
{
	m_impl->SetErrorCallback(callback);
}

