#pragma once

#include "SyncManager.h"

class CriticalSectionStrategy final : public ISyncStrategy
{
public:
	void Initialize(LPCRITICAL_SECTION critical);

	void Lock() override;

	void UnLock() override;

	bool IsLocked() override { return false; }

	void Wait() override {}

private:
	LPCRITICAL_SECTION		m_critical = nullptr;
};

class MutexStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE mutex);
	
	void Lock() override {}

	void UnLock() override;

	bool IsLocked() override;

	void Wait() override;

private:
	HANDLE		m_mutex = nullptr;
};

class EventStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE event);
	
	void Lock() override;

	void UnLock() override;

	bool IsLocked() override;

	void Wait() override;

private:
	HANDLE		m_event = nullptr;
};

class SemaphoreStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE semaphore);

	void Lock() override;

	void UnLock() override;

	bool IsLocked() override { return false; }
	void Wait() override {}

private:
	HANDLE		m_semaphore = nullptr;
};

class WaitableTimerStrategy final : public ISyncStrategy
{
public:
	void Initialize(HANDLE timer);

	void Lock() override;

	void UnLock() override {}

	bool IsLocked() override;

	void Wait() override;

private:
	HANDLE	m_timer = nullptr;
	DWORD	m_period = 100;
};


class SyncManagerImpl
{
public:
	SyncManagerImpl();

	~SyncManagerImpl();

	void SetErrorCallback(std::function<void(const string &)> callback);
	
	weak_ptr<ISyncStrategy> CreateCriticalSectionStrategy();

	weak_ptr<ISyncStrategy> CreateMutexStrategy();

	weak_ptr<ISyncStrategy> CreateEventStrategy();

	weak_ptr<ISyncStrategy> CreateSemaphoreStrategy();

	weak_ptr<ISyncStrategy> CreateTimerStrategy();

private:
	void EchoErrorMessage(const string &error) const;

	CRITICAL_SECTION						m_critical;
	HANDLE									m_mutex;
	HANDLE									m_event;
	HANDLE									m_semaphore;
	HANDLE									m_timer;

	shared_ptr<CriticalSectionStrategy>		m_criticalStrategy;
	shared_ptr<MutexStrategy>				m_mutexStrategy;
	shared_ptr<EventStrategy>				m_eventStrategy;
	shared_ptr<SemaphoreStrategy>			m_semaphoreStrategy;
	shared_ptr<WaitableTimerStrategy>		m_timerStrategy;

	std::function<void(const string &)>		m_errorCallback;
};