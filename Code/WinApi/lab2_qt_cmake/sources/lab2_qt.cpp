#include "stdafx.h"
#include "lab2_qt.h"

#include "ThreadManager.h"
#include "SyncManager.h"

lab2_qt::lab2_qt(QWidget *parent)
	: QMainWindow(parent)
	, m_threadManager(make_shared<ThreadManager>())
	, m_syncManager(make_shared<SyncManager>())
	, m_workInProcess(false)
{
	ui.setupUi(this);

	m_buttons = new QButtonGroup(this);
	m_buttons->addButton(ui.radioButton);
	m_buttons->addButton(ui.radioButton_2);
	m_buttons->addButton(ui.radioButton_3);
	m_buttons->addButton(ui.radioButton_4);
	m_buttons->addButton(ui.radioButton_5);
	m_buttons->addButton(ui.radioButton_6);

	m_timer = new QTimer(this);
	m_timer->setInterval(50);
	connect(m_timer, &QTimer::timeout, this, &lab2_qt::OnCheckWorkCompleted);

	 // устанавливаем маску - двузначное целое число
	ui.lineEdit->setInputMask("DD");

	connect(ui.pushButton, &QPushButton::clicked, this, &lab2_qt::OnStart);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &lab2_qt::OnStop);

	Initialize();
}

void lab2_qt::Initialize()
{
	vector<QListWidget *> listPtrs = 
	{
		ui.listWidget,
		ui.listWidget_2
	};

	auto logFunctionFactory = [listPtrs](int threadNumber) -> ThreadManager::LogCallback
	{
		if (threadNumber >= listPtrs.size())
		{
			return {};
		}

		auto listPtr = listPtrs[threadNumber];
		return [listPtr](int number)
		{
			listPtr->addItem(QString::fromStdString(std::to_string(number)));
		};
	};
	
	m_threadManager->Initialize(logFunctionFactory);
	
	auto errorCallback = [this](const string &message)
	{
		m_errorMessages.push_back(message);
	};
	m_threadManager->SetErrorCallback(errorCallback);
}

void lab2_qt::OnStart()
{
	ui.listWidget->clear();
	ui.listWidget_2->clear();

	auto syncStrategy = GetSyncStrategy();
	if (syncStrategy == SyncPrimitive::INVALID)
	{
		return;
	}

	auto sharedData = make_shared<ThreadSharedData>();
	sharedData->Initialize(m_syncManager->GetSyncStrategy(syncStrategy), GetDelta());
	m_threadManager->SetSharedData(sharedData);
	m_threadManager->CreateThreads();

	SetEnabledGui(false);
	m_threadManager->StartThreads();
	m_workInProcess = true;
	m_timer->start();
}

void lab2_qt::OnStop()
{
	if (m_workInProcess)
	{		
		ui.pushButton_2->setEnabled(false);

		m_timer->stop();

		m_threadManager->StopThreads();

		if (!m_threadManager->WaitThreads(10000))
		{
			m_threadManager->TerminateThreads();
			m_errorMessages.push_back("Threads were terminated forcibly!");
		}

		ShowErrorMessages();
		
		Reset();
		
		ui.pushButton_2->setEnabled(true);
	}
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

int lab2_qt::GetDelta() const
{
	bool isInt = false;
	int delta = ui.lineEdit->text().toInt(&isInt);
	return isInt ? delta : 0;
}

void lab2_qt::Reset()
{	
	m_errorMessages.clear();
	m_workInProcess = false;
	
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

SyncPrimitive lab2_qt::GetSyncStrategy() const
{
	auto button = m_buttons->checkedButton();
	if (!button)
	{
		return SyncPrimitive::INVALID;
	}
	
	auto text = button->text();

	if (text == "no sync")
	{
		return SyncPrimitive::NO_SYNCHRONIZATION;
	}
	else if (text == "critical section")
	{
		return SyncPrimitive::CRITICAL_SECTION;
	}
	else if (text == "semaphore")
	{
		return SyncPrimitive::SEMAPHORE;
	}
	else if (text == "mutex")
	{
		return SyncPrimitive::MUTEX;
	}
	else if (text == "event")
	{
		return SyncPrimitive::EVENT;
	}
	else if (text == "timer")
	{
		return SyncPrimitive::TIMER;
	}

	return SyncPrimitive::INVALID;
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
