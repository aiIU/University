#pragma once

namespace sync
{
	class CriticalSection
	{
	public:
		CriticalSection();
		~CriticalSection();

		void Enter();
		bool TryEnter() const;
		void Leave();

	private:
		struct Impl;
		unique_ptr<Impl>	m_impl;
	};

	class CriticalSectionLock
	{
	public:
		CriticalSectionLock(CriticalSection & cs);
		~CriticalSectionLock();

	private:
		CriticalSection & m_cs;
	};

	class Event
	{
	public:
		explicit Event(bool bInitial = false);
		~Event();

		void WaitForEvent(uint32_t timeout = 0xFFFFFFFF);

		void Set();
		bool IsSet() const;
		void Reset();

	private:
		struct Impl;
		unique_ptr<Impl>	m_impl;
	};
}