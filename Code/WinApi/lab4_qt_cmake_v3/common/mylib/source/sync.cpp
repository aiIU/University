#include "stdafx_lib.h"

#include "sync.h"

#include <Windows.h>
// #include <synchapi.h>
// #include <handleapi.h>
// #include <winbase.h>

namespace sync
{
	struct CriticalSection::Impl
	{
		CRITICAL_SECTION	cs;
	};

	CriticalSection::CriticalSection()
		: m_impl(make_unique<Impl>())
	{
		InitializeCriticalSection(&m_impl->cs);
	}

	CriticalSection::~CriticalSection()
	{
		DeleteCriticalSection(&m_impl->cs);
	}

	void CriticalSection::Enter()
	{
		EnterCriticalSection(&m_impl->cs);
	}

	bool CriticalSection::TryEnter() const
	{
		return TryEnterCriticalSection(&m_impl->cs);
	}

	void CriticalSection::Leave()
	{
		LeaveCriticalSection(&m_impl->cs);
	}

	CriticalSectionLock::CriticalSectionLock(CriticalSection & cs)
		: m_cs(cs)
	{
		m_cs.Enter();
	}

	CriticalSectionLock::~CriticalSectionLock()
	{
		m_cs.Leave();
	}

	struct Event::Impl
	{
		HANDLE handle;
	};

	Event::Event(bool bInitial)
		: m_impl(make_unique<Impl>())
	{
		m_impl->handle = CreateEventA(nullptr, true, bInitial, nullptr);
	}

	Event::~Event()
	{
		CloseHandle(m_impl->handle);
	}

	void Event::WaitForEvent(uint32_t timeout)
	{
		WaitForSingleObject(m_impl->handle, timeout);
	}

	void Event::Set()
	{
		SetEvent(m_impl->handle);
	}

	bool Event::IsSet() const
	{
		return WaitForSingleObject(m_impl->handle, 0) == WAIT_OBJECT_0;
	}

	void Event::Reset()
	{
		ResetEvent(m_impl->handle);
	}
}
