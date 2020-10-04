#include "stdafx.h"
#include "Worker.h"

ClientWorker::~ClientWorker()
{
	ForceStopWork();
}

bool ClientWorker::Initialize(int workerId, int ttl, ipc::Receiver receiver, LogCallback onLog, UpdateTTLCallback onTick)
{
	if (m_isInitialized)
	{
		return false;
	}
	m_workerId = workerId;
	m_receiver = receiver;
	m_ttl = ttl;

	m_logger = onLog;
	m_ttlUpdateCallback = onTick;

	if (!Run())
	{
		return false;
	}

	// show initial ttl
	m_ttlUpdateCallback(m_ttl);

	m_isInitialized = true;
	return true;
}

void ClientWorker::ForceStopWork()
{
	if (m_isInitialized && m_mainLoopThread.joinable())
	{
		m_forseStop = true;
		m_mainLoopThread.join();
		m_workIsCompleted = true;
		
		SendWorkCompleted();
	}
}

void ClientWorker::LauncherListen()
{
	while (!m_forseStop)
	{
		ipc::Message msg;
		if (!ipc::WaitMessageFor(25, msg))
		{
			continue;
		}

		if (msg.GetType() == ipc::MessageType::FORCE_CLOSE)
		{
			LogMessage("Launcher: FORSE_CLOSE");
			SendWorkCompleted();
			break;
		}

		if (msg.GetType() == ipc::MessageType::TICK)
		{
			LogMessage("Launcher: TICK");
			m_ttl = std::max(m_ttl - 1, 0);
			m_ttlUpdateCallback(m_ttl);

			if (m_ttl == 0)
			{
				LogMessage("Trying to send CLOSED.");
				bool res = SendWorkCompleted();
				LogMessage(res ? "Success" : "Failure");
				break;
			}
		}
	}
	m_workIsCompleted = true;
}

void ClientWorker::LogMessage(const string& message)
{
	m_logger(message);
}

bool ClientWorker::Run()
{
	m_mainLoopThread = std::thread([this]()
	{
		LogMessage("Listener is running.");
		LauncherListen();
	});

	HANDLE handle = m_mainLoopThread.native_handle();
	DWORD mainLoopId = GetThreadId(handle);
	
	LogMessage("Trying to change receiver on " + std::to_string(mainLoopId));
	if (!SendChangeReceiver(mainLoopId))
	{
		m_forseStop = true;
		m_mainLoopThread.join();
		return false;
	}
	return true;
}

bool ClientWorker::SendChangeReceiver(ipc::Receiver newReceiver)
{
	auto changeReceiver = ipc::Message(ipc::MessageType::RECEIVER_CHANGED, newReceiver, m_workerId);
	return SendMessage(changeReceiver, m_receiver);
}

bool ClientWorker::SendWorkCompleted()
{
	auto workComplete = ipc::Message(ipc::MessageType::CLOSED, m_workerId);
	return SendMessage(workComplete, m_receiver);
}