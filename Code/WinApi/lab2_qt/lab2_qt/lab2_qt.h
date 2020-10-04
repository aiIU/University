#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab2_qt.h"

class ThreadManager;
struct ThreadData;

class SyncManager;
class ISyncStrategy;

class lab2_qt : public QMainWindow
{
	Q_OBJECT
public:
	lab2_qt(QWidget *parent = Q_NULLPTR);

private slots:
	void OnSetSyncStrategy(QAbstractButton* button);
	void OnStart();
	void OnStop();
	void OnDeltaEdit(const QString & value);
	void OnCheckWorkCompleted();
private:
	void SetEnabledGui(bool on);
	void Reset();
	void CheckRaceCondition();
	int GetUserDelta() const;

	void ShowErrorMessages();

	Ui::lab2_qtClass					ui;

	shared_ptr<ThreadData>				m_threadData;
	shared_ptr<ThreadManager>			m_threadManager;
	shared_ptr<SyncManager>				m_syncManager;

	bool								m_workInProcess;
	QPointer<QTimer>					m_timer;
	vector<int>							m_out1;
	vector<int>							m_out2;

	vector<string>						m_errorMessages;
};

