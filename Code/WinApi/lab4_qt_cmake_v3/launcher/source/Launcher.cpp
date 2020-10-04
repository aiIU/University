#include "stdafx.h"
#include "Launcher.h"

#include "sync.h"
#include "ipc.h"
#include "utils.h"

#include "GeneratorId.h"

ServerWorker::ServerWorker(ipc::Receiver receiver)
	: m_receiver(receiver)
{
}

bool ServerWorker::SendTick()
{
	auto tick = ipc::Message(ipc::MessageType::TICK);
	return SendMessage(tick, m_receiver);
}

bool ServerWorker::SendForceClose()
{
	auto forceClose = ipc::Message(ipc::MessageType::FORCE_CLOSE);
	return SendMessage(forceClose, m_receiver);
}

void ServerWorker::UpdateReceiver(ipc::Receiver newReceiver)
{
	m_receiver = newReceiver;
}

Launcher::Launcher()
	: m_generatorId(make_shared<GeneratorId>())
{
	m_threadInput = std::thread([this]()
	{
		ListenWorkers();
	});
	
	m_threadOutput = std::thread([this]()
	{
		MainLoop();
	});
}

Launcher::~Launcher()
{
	m_needForseStop = true;

	m_threadInput.join();
	m_threadOutput.join();

	for (auto && worker : m_workers)
	{
		worker.second->SendForceClose();
	}
}

void Launcher::SetMaximumWorkers(int number)
{
	sync::CriticalSectionLock lock(m_criticalSection);
	if (m_maxWorkers != number)
	{
		LogMessage("Maximum number of worker changed on " + std::to_string(number));	
	}
	m_maxWorkers = number;
}

int Launcher::GetCurrentWorkersNumber() const
{
	sync::CriticalSectionLock lock(m_criticalSection);
	return static_cast<int>(m_workers.size());
}

void Launcher::Tick()
{
	m_tickEvent.Set();
}

bool Launcher::CreateWorker()
{
	// Генерируем новый айди для вокера (от 0 до 100)
	auto id = m_generatorId->Next();
	// Задаем время жизни воркера (от 3 до 7 секунд)
	auto ttl = GetRandomNumber(3, 7);
	// Узнаём хендл потока прослушивания воркеров
	HANDLE handle = m_threadInput.native_handle();
	// Получаем его айди
	int parentThreadId = GetThreadId(handle);
	// Передаём все это новому воркеру
	string commandLine = "worker.exe " + std::to_string(id) + " " + std::to_string(ttl) + " " + std::to_string(parentThreadId);

	LogMessage("\"" + commandLine + "\" is creating.");

	STARTUPINFOA sInfo;
	memset(&sInfo, 0, sizeof sInfo);
	sInfo.dwX = 1000 / 2 + GetRandomNumber(-200, 200);
	sInfo.dwY = 800 / 2 + GetRandomNumber(-50, 50);

	PROCESS_INFORMATION pInfo;
	memset(&pInfo, 0, sizeof pInfo);

	BOOL res = CreateProcessA(nullptr, &commandLine[0], nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, nullptr, &sInfo, &pInfo);
	if (res == FALSE)
	{
		auto error = utils::GetLastErrorMessage("CreateProcess");
		LogError(error);
		m_generatorId->Free(id);
		return false;
	}

	CloseHandle(pInfo.hProcess);

	{
		sync::CriticalSectionLock lock(m_criticalSection);
		auto worker = make_shared<ServerWorker>(pInfo.dwThreadId);
		m_workers.emplace(id, worker);

		ResumeThread(pInfo.hThread);
		CloseHandle(pInfo.hThread);
	}

	LogMessage("Worker was been created successfully.");
	return true;
}

void Launcher::MainLoop()
{
	while (!m_needForseStop)
	{
		m_tickEvent.WaitForEvent(50);
		if (!m_tickEvent.IsSet())
		{
			continue;
		}

		{
			sync::CriticalSectionLock lock(m_criticalSection);
			for (auto && [workerId, worker] : m_workers)
			{
				worker->SendTick();
			}
			if (m_maxWorkers > m_workers.size())
			{
				CreateWorker();
			}
		}
		m_tickEvent.Reset();
	}
}

void Launcher::SetLogCallback(std::function<void(const string&)> callback)
{
	sync::CriticalSectionLock lock(m_criticalSection);
	m_logCallback = callback;
}

void Launcher::SetErrorCallback(std::function<void(const string&)> callback)
{
	sync::CriticalSectionLock lock(m_criticalSection);
	m_errorCallback = callback;
}

int Launcher::GetRandomNumber(int from, int to)
{
	std::uniform_int_distribution<int> dist(from, to);
	return dist(m_random);
}

void Launcher::LogError(const string & message)
{
	if (m_errorCallback)
	{
		sync::CriticalSectionLock lock(m_criticalSection);
		m_errorCallback(message);
	}
}

void Launcher::LogMessage(const string& message)
{
	if (m_logCallback)
	{
		sync::CriticalSectionLock lock(m_criticalSection);
		m_logCallback(message);
	}
}

void Launcher::ListenWorkers()
{
	while (!m_needForseStop)
	{
		ipc::Message msg;
		if (!ipc::WaitMessageFor(25, msg))
		{
			continue;
		}
		LogMessage("Message received.");
		
		auto id = msg.GetWorkerId();
		if (msg.GetType() == ipc::MessageType::CLOSED)
		{
			sync::CriticalSectionLock lock(m_criticalSection);
			LogMessage("Worker: CLOSED");
			auto it = m_workers.find(id);
			if (it != m_workers.end())
			{
				m_generatorId->Free(it->first);
				m_workers.erase(it);
				LogMessage("Worker #" + std::to_string(id) + " completed his work.");
			}
		}
		else if (msg.GetType() == ipc::MessageType::RECEIVER_CHANGED)
		{
			LogMessage("Worker: RECEIVER_CHANGED");
			auto receiver = msg.GetNewReceiver();
			sync::CriticalSectionLock lock(m_criticalSection);
			auto it = m_workers.find(id);
			if (it != m_workers.end())
			{
				it->second->UpdateReceiver(receiver);
				LogMessage("Worker #" + std::to_string(id) + " changed its id of receiver thread on " + std::to_string(receiver.id));
			}
		}
	}
}
