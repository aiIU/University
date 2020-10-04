#pragma once
#include "ui_launcher.h"

class LauncherGui : public QMainWindow
{
	Q_OBJECT
public:
	enum class Message
	{
		TICK = 0x100,
		CLOSE
	};

	LauncherGui(QWidget * parent = nullptr);
	~LauncherGui();

	void MainLoop();

private:
	void OnCheckThreadsAlive();
	void OnThreadsComplete();

	void CreateWorker();

	enum class LogMessageType
	{
		LM_ERROR,
		LM_CREATE_WORKER,
		LM_TEXT
	};
	void LogMessage(const string & message, LogMessageType type = LogMessageType::LM_TEXT);

	string GetLastError(const string & functionName);
	string ErrorCodeToString(DWORD code, const string &functionName);

	int GetMaxChildrenNumber() const;

	std::mutex						m_mutex;
	std::mutex						m_logMutex;
	vector<DWORD>					m_childrenThreadIds;

	std::mt19937					m_random;
	
	std::atomic_bool	m_forseStop;
	std::thread			m_mainLoopThread;


	QPointer<QTimer>	m_threadsChecker;

	Ui::Launcher		m_ui;
};
