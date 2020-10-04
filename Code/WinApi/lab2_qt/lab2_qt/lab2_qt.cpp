#include "stdafx.h"
#include "lab2_qt.h"

#include "ThreadManager.h"
#include "SyncApi.h"

lab2_qt::lab2_qt(QWidget *parent)
	: QMainWindow(parent)
	, m_threadData(make_shared<ThreadData>())
	, m_threadManager(make_shared<ThreadManager>())
	, m_syncManager(make_shared<SyncManager>())
	, m_workInProcess(false)
{
	ui.setupUi(this);

	auto radioGroup = new QButtonGroup(this);
	radioGroup->addButton(ui.radioButton);
	radioGroup->addButton(ui.radioButton_2);
	radioGroup->addButton(ui.radioButton_3);
	radioGroup->addButton(ui.radioButton_4);
	radioGroup->addButton(ui.radioButton_5);
	radioGroup->addButton(ui.radioButton_6);
	connect(radioGroup, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), 
		this, &lab2_qt::OnSetSyncStrategy);
	OnSetSyncStrategy(radioGroup->checkedButton());

	m_timer = new QTimer(this);
	m_timer->setInterval(50);
	connect(m_timer, &QTimer::timeout, this, &lab2_qt::OnCheckWorkCompleted);

	 // устанавливаем маску - двузначное целое число
	ui.lineEdit->setInputMask("DD");
	connect(ui.lineEdit, &QLineEdit::textEdited, this, &lab2_qt::OnDeltaEdit);

	connect(ui.pushButton, &QPushButton::clicked, this, &lab2_qt::OnStart);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &lab2_qt::OnStop);

	auto errorCallback = [this](const string &message)
	{
		m_errorMessages.push_back(message);
	};
	m_syncManager->SetErrorCallback(errorCallback);
	m_threadManager->SetErrorCallback(errorCallback);

	Reset();
}

void lab2_qt::OnSetSyncStrategy(QAbstractButton* button)
{
	auto text = button->text();
	if (text == "no sync")
	{
		m_threadData->m_sync = m_syncManager->GetNoSyncStrategy();
	}
	else if (text == "critical section")
	{
		m_threadData->m_sync = m_syncManager->GetCriticalSectionStrategy();
	}
	else if (text == "semaphore")
	{
		m_threadData->m_sync = m_syncManager->GetSemaphoreStrategy();
	}
	else if (text == "mutex")
	{
		m_threadData->m_sync = m_syncManager->GetMutexStrategy();
	}
	else if (text == "event")
	{
		m_threadData->m_sync = m_syncManager->GetEventStrategy();
	}
	else if (text == "timer")
	{
		m_threadData->m_sync = m_syncManager->GetTimerStrategy();
	}
}

void lab2_qt::OnStart()
{
	ui.listWidget->clear();
	ui.listWidget_2->clear();

	vector<QListWidget*> listPtrs = 
	{
		ui.listWidget,
		ui.listWidget_2
	};

	auto logFunctionFactory = [listPtrs](int threadNumber)
	{
		auto list = listPtrs[threadNumber % listPtrs.size()];
		return [list](int number) mutable
		{
			list->addItem(QString::fromStdString(std::to_string(number)));			
		};
	};

	m_threadManager->CreateThreads(logFunctionFactory, m_threadData, listPtrs.size());

	SetEnabledGui(false);
	m_threadManager->StartThreads();
	m_workInProcess = true;
	m_timer->start();
}

void lab2_qt::OnStop()
{
	if (m_workInProcess)
	{		
		m_timer->stop();
		m_threadData->m_forceStop.store(true, std::memory_order_release);

		m_threadManager->WaitThreads(1000);
		if (m_threadManager->ThreadsInProcess())
		{
			m_threadManager->TerminateThreads();
		}
		ShowErrorMessages();
		
		Reset();
	}
}

void lab2_qt::OnDeltaEdit(const QString& value)
{
	m_threadData->m_delta = GetUserDelta();
}

void lab2_qt::OnCheckWorkCompleted()
{
	if (m_threadManager->ThreadsInProcess())
	{
		return;
	}
	m_timer->stop();
	CheckRaceCondition();
	ShowErrorMessages();
	Reset();
}

void lab2_qt::SetEnabledGui(bool on)
{
	ui.pushButton->setEnabled(on);
	ui.lineEdit->setEnabled(on);
	ui.groupBox->setEnabled(on);
}

int lab2_qt::GetUserDelta() const
{
	bool isInt = false;
	int delta = ui.lineEdit->text().toInt(&isInt);
	return isInt ? delta : 0;
}

void lab2_qt::Reset()
{	
	m_errorMessages.clear();
	m_workInProcess = false;
	
	m_threadData->m_forceStop.store(false, std::memory_order_release);
	m_threadData->m_delta = GetUserDelta();
	m_threadData->m_data = 0;
	
	SetEnabledGui(true);	
}

void lab2_qt::CheckRaceCondition()
{
	if (ui.listWidget->count() != ui.listWidget_2->count())
	{
		QMessageBox::critical(this, "Race Condition Checker", "Two threads made different number of records!");
		return;
	}

	int incorrectIndex = -1;
	auto count = ui.listWidget->count();
	for (int i = 0; i < count; ++i)
	{
		auto item1 = ui.listWidget->item(i);
		auto item2 = ui.listWidget_2->item(i);

		if (item1->text() != item2->text())
		{
			incorrectIndex = i;
			item1->setSelected(true);
			item2->setSelected(true);
			break;
		}
	}

	bool isRaceCondition = incorrectIndex != -1;
	if (isRaceCondition)
	{
		auto text = "Race condition was detected on " + QString::number(incorrectIndex + 1) + " line!";
		QMessageBox::warning(this, "Race Condition Checker", text);
	}
	else
	{
		auto text = "Race condition did not detected!";
		QMessageBox::information(this, "Race Condition Checker", text);
	}
}

void lab2_qt::ShowErrorMessages()
{
	if (m_errorMessages.empty())
	{
		return;
	}

	QString out;
	int i = 1;
	for (auto && message : m_errorMessages)
	{
		out += QString::fromStdString(std::to_string(i)) + ". ";
		out += QString::fromStdString(message) + "\n";
		++i;
	}
	QMessageBox::critical(this, "Errors", out);
}
