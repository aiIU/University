#pragma once
#include "ui_WorkerGui.h"
#include "sync.h"

class ClientWorker;

class WorkerGui : public QMainWindow
{
	Q_OBJECT
public:
	WorkerGui(QWidget * parent = nullptr);
	~WorkerGui();

	// Инициализируем worker-а настройками из командной строки
	// argv[1] - worker id (число от 0 до 100), argv[2] - ttl, argv[3] - parent id
	bool Initialize(int argc, char** argv);

private:
	void OnCheckWorkComplete();

	void ShowTtl(int ttl);
	void LogMessage(const string & message);

	sync::CriticalSection		m_cs;
	unique_ptr<ClientWorker>	m_worker;
	QPointer<QTimer>			m_timer;

	Ui::WorkerGui			m_ui;
};
