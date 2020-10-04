#include "stdafx.h"
#include "lab1_qt.h"

#include <QMessageBox>
#include <QInputDialog>

#include "ProcessManager.h"

lab1_qt::lab1_qt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("Process Manager");
	setWindowIcon(QIcon(":/Resources/icon.png"));

	connect(ui.startButton, &QPushButton::clicked, this, &lab1_qt::OnCreateProcess);
	connect(ui.stopButton, &QPushButton::clicked, this, &lab1_qt::OnStopProcess);

	m_processManager = make_shared<ProcessManager>();
}

void lab1_qt::OnCreateProcess()
{
	string name;
	bool res = RequestString("Enter application name or full path.", name);
	if (!res)
	{
		return;
	}

	if (name.empty())
	{
		ShowErrorMessage("Empty name.");
		return;	
	}

	try
	{
		auto handle = m_processManager->CreateProcess(name);

		auto str = string(100, '\0');
		std::snprintf(&str.front(), str.size(), "%d: %p", ui.listWidget->count() + 1, handle);

		ui.listWidget->addItem(QString::fromStdString(str));
	}
	catch (const std::exception &error)
	{
		ShowErrorMessage(error.what());
	}
}

void lab1_qt::OnStopProcess()
{
	auto items = ui.listWidget->selectedItems();
	if (items.empty())
	{
		return;
	}

	auto item = items[0];
	auto str = item->text().toStdString();
	HANDLE handle;
	sscanf_s(str.c_str(), "%*d: %p", &handle);

	try
	{
		m_processManager->TerminateProcess(handle);
		delete ui.listWidget->takeItem(ui.listWidget->row(item));
	} catch (const std::exception &error)
	{
		ShowErrorMessage(error.what());
	}
}

void lab1_qt::ShowErrorMessage(const string& message)
{
	auto text = QString::fromStdString(message);
	QMessageBox::critical(this, "Error", text);
}

bool lab1_qt::RequestString(const string& hint, string & out)
{
	auto title = QString("Creating process...");
	auto label = QString::fromStdString(hint);
	auto defaultValue = QString::fromStdString("notepad");

	bool result;
	auto qout = QInputDialog::getText(this, title, label, QLineEdit::Normal, defaultValue, &result);
	out = qout.toStdString();

	return result;
}
