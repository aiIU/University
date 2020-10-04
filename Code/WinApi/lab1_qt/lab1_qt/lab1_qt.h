#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab1_qt.h"

class ProcessManager;

class lab1_qt : public QMainWindow
{
	Q_OBJECT

public:
	lab1_qt(QWidget *parent = Q_NULLPTR);

private slots:
	void OnCreateProcess();
	void OnStopProcess();

private:
	void ShowErrorMessage(const string & message);

	bool RequestString(const string & hint, string & out);

	Ui::lab1_qtClass ui;

	shared_ptr<ProcessManager> m_processManager;
};
