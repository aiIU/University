#pragma once
#include "ui_worker.h"

class Worker : public QMainWindow
{
	Q_OBJECT
public:
	enum class Message
	{
		TICK = 0x100,
		CLOSE
	};

	Worker(QWidget * parent = nullptr);
	~Worker();

	// Инициализируем worker-а настройками из командной строки
	// argv[1] - id, argv[2] - ttl, argv[3] - parent id
	void Initialize(int argc, char **argv);

signals:
	void Close();

private slots:
	void OnClose();

private:
	void MainLoop();

	void OnTick();

	void UpdateVisualTTL();

	void LogMessage(const string & message);
	void ShowErrorMessage(const string & message);

	string GetLastError(const string & functionName);
	string ErrorCodeToString(DWORD code, const string &functionName);

	int						m_timeToLive;
	int						m_idWorker;
	DWORD					m_parentId;
	
	std::atomic_bool		m_isInitialized;
	std::atomic_bool		m_forseStop;
	std::thread				m_mainLoopThread;

	Ui::Worker				m_ui;
};