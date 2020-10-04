#pragma once

#include "ipc.h"

class ClientWorker
{
public:
	using UpdateTTLCallback = std::function<void(int)>;
	using LogCallback = std::function<void(const string &)>;

	~ClientWorker();

	// receiver - айди сервера, которому отправлять сообщения
	bool Initialize(int workerId, int ttl, ipc::Receiver receiver, LogCallback onLog, UpdateTTLCallback onTick);

	void ForceStopWork();
	bool IsWorkCompleted() const { return m_workIsCompleted; }

private:
	// Запупуск вспомогательного рабочего потока
	bool Run();

	// Сообщение для уведомления сервера, чтобы тот сменил айди клиента на новый
	// newReceiver - новый айди клиента
	bool SendChangeReceiver(ipc::Receiver newReceiver);
	
	// Сообщение для уведомления сервера, что клиент завершил работу
	bool SendWorkCompleted();

	// Прослушивание сообщений от сервера
	void LauncherListen();

	void LogMessage(const string & message);

	bool				m_isInitialized {false};
	int					m_workerId {0};
	int					m_ttl {0};
	ipc::Receiver		m_receiver;

	UpdateTTLCallback	m_ttlUpdateCallback;
	LogCallback			m_logger;

	std::atomic_bool	m_workIsCompleted {false};
	std::atomic_bool	m_forseStop {false};
	std::thread			m_mainLoopThread;
};