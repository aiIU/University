#include "stdafx.h"
#include "Launcher.h"

CritSection::CritSection()
{
	InitializeCriticalSection(&m_crit);
}

CritSection::~CritSection()
{
	DeleteCriticalSection(&m_crit);
}

void CritSection::Lock()
{
	EnterCriticalSection(&m_crit);	
}

void CritSection::Unlock()
{
	LeaveCriticalSection(&m_crit);
}

Launcher::Launcher()
{
	GenerateIds();
}

void Launcher::SetMaximumWorkers(int number)
{
	m_crit.Lock();
	m_maxWorkers = number;
	m_crit.Unlock();
}

int Launcher::GetWorkersNumber() const
{
	m_crit.Lock();
	int n = m_workers.size();
	m_crit.Unlock();
	return n;
}

void Launcher::CreateWorker()
{

}

void Launcher::GenerateIds()
{
	m_freeIds = queue<int>();
	m_busyIds = queue<int>();
	for (int i = GetWorkersNumber(); i > 0; --i)
	{
		m_freeIds.push(i);
	}
}

int Launcher::GetId()
{
	if (m_freeIds.empty())
	{
		return -1;
	}

	int id = m_freeIds.front();
	m_freeIds.pop();
	m_busyIds.push(id);
	return id;
}

