#pragma once

#include "ui_lab2_qt.h"

class ThreadManager;
class SyncManager;

enum class SyncPrimitive;

class lab2_qt : public QMainWindow
{
	Q_OBJECT
public:
	lab2_qt(QWidget *parent = Q_NULLPTR);

	void Initialize();

private slots:
	void OnStart();
	void OnStop();
	void OnCheckWorkCompleted();

private:

	void SetEnabledGui(bool on);
	void Reset();
	void CheckRaceCondition();
	
	SyncPrimitive GetSyncStrategy() const;
	int GetDelta() const;

	void ShowErrorMessages();

	Ui::lab2_qt						ui;
	QButtonGroup *					m_buttons;
	
	shared_ptr<ThreadManager>		m_threadManager;
	shared_ptr<SyncManager>			m_syncManager;

	bool							m_workInProcess;
	QPointer<QTimer>				m_timer;
	vector<int>						m_out1;
	vector<int>						m_out2;

	vector<string>					m_errorMessages;
};

