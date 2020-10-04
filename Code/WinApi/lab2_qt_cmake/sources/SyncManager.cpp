#include "stdafx.h"
#include "SyncManager.h"

#ifdef WIN32
#include "SyncManagerWinImpl.h"
#else
#error This platform does not supported
#endif

class NoSyncStrategy final : public ISyncStrategy
{
public:
	void Lock() override {}
	void UnLock() override {}
	bool IsLocked() override { return false; }
	void Wait() override {}
};

SyncManager::SyncManager()
	: m_impl(new SyncManagerImpl)
{
}

SyncManager::~SyncManager()
{
	delete m_impl;
}

weak_ptr<ISyncStrategy> SyncManager::GetSyncStrategy(SyncPrimitive primitive)
{
	switch (primitive)
	{
	case SyncPrimitive::NO_SYNCHRONIZATION:
		return GetNoSyncStrategy();
	case SyncPrimitive::CRITICAL_SECTION:
		return GetCriticalSectionStrategy();
	case SyncPrimitive::TIMER:
		return GetTimerStrategy();
	case SyncPrimitive::SEMAPHORE:
		return GetSemaphoreStrategy();
	case SyncPrimitive::MUTEX:
		return GetMutexStrategy();
	case SyncPrimitive::EVENT:
		return GetEventStrategy();
	default:
		return GetNoSyncStrategy();
	}
}

weak_ptr<ISyncStrategy> SyncManager::GetNoSyncStrategy()
{
	if (!m_noSyncStrategy)
	{
		m_noSyncStrategy = make_shared<NoSyncStrategy>();	
	}
	return m_noSyncStrategy;
}

weak_ptr<ISyncStrategy> SyncManager::GetCriticalSectionStrategy()
{
	return m_impl->CreateCriticalSectionStrategy();
}

weak_ptr<ISyncStrategy> SyncManager::GetTimerStrategy()
{
	return m_impl->CreateTimerStrategy();
}

weak_ptr<ISyncStrategy> SyncManager::GetSemaphoreStrategy()
{
	return m_impl->CreateSemaphoreStrategy();
}

weak_ptr<ISyncStrategy> SyncManager::GetMutexStrategy()
{
	return m_impl->CreateMutexStrategy();
}

weak_ptr<ISyncStrategy> SyncManager::GetEventStrategy()
{
	return m_impl->CreateEventStrategy();
}

void SyncManager::SetErrorCallback(std::function<void(const string&)> callback)
{
	m_impl->SetErrorCallback(callback);
}

