#pragma once
#include "ui_Synchronizer.h"

#include "ThreadManager.h"

class Synchronizer : public QMainWindow
{
	Q_OBJECT
public:
	Synchronizer(QWidget * parent = nullptr);

	void Initialize();

private slots:
	void OnStart();
	void OnReset();

private:
	// Функции, возвращающие данные введенные пользователем из формы
	SyncType GetUserSyncType() const;
	int GetUserDelta() const;

	ThreadManager			m_threadManager;

	QButtonGroup *			m_buttons;
	Ui::Synchronizer		m_ui;
};