#include "stdafx.h"
#include "SyncManagerWinImpl.h"
#include "WinApiUtils.h"

// <-------------------- CriticalSectionStrategy -------------------->

void CriticalSectionStrategy::Initialize(LPCRITICAL_SECTION critical)
{
	m_critical = critical;
}

void CriticalSectionStrategy::Lock()
{
	EnterCriticalSection(m_critical);	
}

void CriticalSectionStrategy::UnLock()
{
	LeaveCriticalSection(m_critical);
}

// <-------------------- MutexStrategy -------------------->

void MutexStrategy::Initialize(HANDLE mutex)
{
	m_mutex = mutex;
}

void MutexStrategy::UnLock()
{
	ReleaseMutex(m_mutex);
}

bool MutexStrategy::IsLocked()
{
	return WaitForSingleObject(m_mutex, 0) != WAIT_OBJECT_0;
}

void MutexStrategy::Wait()
{
	WaitForSingleObject(m_mutex, INFINITE);
}

// <-------------------- EventStrategy -------------------->

void EventStrategy::Initialize(HANDLE event)
{
	m_event = event;
}

void EventStrategy::Lock()
{
	ResetEvent(m_event);
}

void EventStrategy::UnLock()
{
	SetEvent(m_event);
}

bool EventStrategy::IsLocked()
{
	return WaitForSingleObject(m_event, 0) != WAIT_OBJECT_0;
}

void EventStrategy::Wait()
{
	WaitForSingleObject(m_event, INFINITE);
}

// <-------------------- SemaphoreStrategy -------------------->

void SemaphoreStrategy::Initialize(HANDLE semaphore)
{
	m_semaphore = semaphore;
}

void SemaphoreStrategy::Lock()
{
	WaitForSingleObject(m_semaphore, INFINITE);	
}

void SemaphoreStrategy::UnLock()
{
	ReleaseSemaphore(m_semaphore, 1, nullptr);	
}

// <-------------------- WaitableTimerStrategy -------------------->

void WaitableTimerStrategy::Initialize(HANDLE timer) 
{
	m_timer = timer;
}

void WaitableTimerStrategy::Lock()
{
	SetWaitableTimer(m_timer, nullptr, m_period, nullptr, nullptr, true);
}

bool WaitableTimerStrategy::IsLocked()
{
	auto res = WaitForSingleObject(m_timer, 0);
	return res == WAIT_TIMEOUT;
}

void WaitableTimerStrategy::Wait()
{
	WaitForSingleObject(m_timer, m_period);
}

// <-------------------- MutexStrategy -------------------->


SyncManagerImpl::SyncManagerImpl()
	: m_mutex(nullptr)
	, m_event(nullptr)
	, m_semaphore(nullptr)
	, m_timer(nullptr)
{
	std::memset(&m_critical, 0, sizeof(CRITICAL_SECTION));
}

SyncManagerImpl::~SyncManagerImpl()
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
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CloseHandle");
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
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CloseHandle");
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
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CloseHandle");
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
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CloseHandle");
			EchoErrorMessage(msg);
		}
	}
}

void SyncManagerImpl::SetErrorCallback(std::function<void(const string &)> callback)
{
	m_errorCallback = callback;	
}

weak_ptr<ISyncStrategy> SyncManagerImpl::CreateCriticalSectionStrategy()
{
	if (!m_criticalStrategy)
	{
		m_criticalStrategy = make_shared<CriticalSectionStrategy>();
		InitializeCriticalSection(&m_critical);
		m_criticalStrategy->Initialize(&m_critical);
	}
	return m_criticalStrategy;
}

weak_ptr<ISyncStrategy> SyncManagerImpl::CreateMutexStrategy()
{
	if (!m_mutexStrategy)
	{
		m_mutex = CreateMutexA(nullptr, false, nullptr);
		if (!m_mutex)
		{
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CreateMutex");
			EchoErrorMessage(msg);
			return {};
		}
		m_mutexStrategy = make_shared<MutexStrategy>();
		m_mutexStrategy->Initialize(m_mutex);
	}
	return m_mutexStrategy;
}

weak_ptr<ISyncStrategy> SyncManagerImpl::CreateEventStrategy()
{
	if (!m_eventStrategy)
	{
		m_event = CreateEventA(nullptr, true, true, nullptr);
		if (!m_event)
		{
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CreateEvent");
			EchoErrorMessage(msg);
			return {};
		}
		m_eventStrategy = make_shared<EventStrategy>();
		m_eventStrategy->Initialize(m_event);

	}
	return m_eventStrategy;
}

weak_ptr<ISyncStrategy> SyncManagerImpl::CreateSemaphoreStrategy()
{
	if (!m_semaphoreStrategy)
	{
		m_semaphore = CreateSemaphoreA(nullptr, 1, 1, nullptr);
		if (!m_semaphore)
		{
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CreateSemaphore");
			EchoErrorMessage(msg);
			return {};
		}
		m_semaphoreStrategy = make_shared<SemaphoreStrategy>();
		m_semaphoreStrategy->Initialize(m_semaphore);
	}
	return m_semaphoreStrategy;
}

weak_ptr<ISyncStrategy> SyncManagerImpl::CreateTimerStrategy()
{
	if (!m_timerStrategy)
	{
		m_timer = CreateWaitableTimerA(nullptr, TRUE, nullptr);
		if (!m_timer)
		{
			auto msg = WinApiUtils::ErrorCodeToString(GetLastError(), "CreateWaitableTimer");
			EchoErrorMessage(msg);
			return {};
		}
		m_timerStrategy = make_shared<WaitableTimerStrategy>();
		m_timerStrategy->Initialize(m_timer);
	}
	return m_timerStrategy;
}

void SyncManagerImpl::EchoErrorMessage(const string &error) const
{
	if (m_errorCallback)
	{
		m_errorCallback(error);
	}
}