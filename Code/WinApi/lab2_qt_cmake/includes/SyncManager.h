#pragma once

class ISyncStrategy
{
public:
	virtual ~ISyncStrategy() = default;

	virtual void Lock() = 0;
	virtual void UnLock() = 0;
	virtual bool IsLocked() = 0;
	virtual void Wait() = 0;
};

enum class SyncPrimitive
{
	NO_SYNCHRONIZATION,
	CRITICAL_SECTION,
	TIMER,
	SEMAPHORE,
	MUTEX,
	EVENT,
	INVALID
};

class SyncManagerImpl;

class SyncManager
{
public:

	SyncManager();
	~SyncManager();

	weak_ptr<ISyncStrategy> GetSyncStrategy(SyncPrimitive primitive);

	void SetErrorCallback(std::function<void(const string &)> callback);

private:
	weak_ptr<ISyncStrategy> GetNoSyncStrategy();
	weak_ptr<ISyncStrategy> GetCriticalSectionStrategy();
	weak_ptr<ISyncStrategy> GetTimerStrategy();
	weak_ptr<ISyncStrategy> GetSemaphoreStrategy();
	weak_ptr<ISyncStrategy> GetMutexStrategy();
	weak_ptr<ISyncStrategy> GetEventStrategy();

	shared_ptr<ISyncStrategy> m_noSyncStrategy;

	SyncManagerImpl * m_impl;
};