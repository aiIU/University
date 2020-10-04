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

class SyncManager
{
public:
	SyncManager();
	~SyncManager();
	
	shared_ptr<ISyncStrategy> GetNoSyncStrategy();
	shared_ptr<ISyncStrategy> GetCriticalSectionStrategy();
	shared_ptr<ISyncStrategy> GetTimerStrategy();
	shared_ptr<ISyncStrategy> GetSemaphoreStrategy();
	shared_ptr<ISyncStrategy> GetMutexStrategy();
	shared_ptr<ISyncStrategy> GetEventStrategy();
	
	void SetErrorCallback(std::function<void(const string &)> callback);

private:
	class SyncManagerImpl;
	SyncManagerImpl * m_impl;
};