#include "stdafx.h"
#include "Synchronizer.h"

Synchronizer::Synchronizer(QWidget* parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_buttons = new QButtonGroup(this);
	m_buttons->addButton(m_ui.radioButton_0);
	m_buttons->addButton(m_ui.radioButton_1);
	m_buttons->addButton(m_ui.radioButton_2);
	m_buttons->addButton(m_ui.radioButton_3);
	m_buttons->addButton(m_ui.radioButton_4);
	m_ui.radioButton_0->setChecked(true);

	m_ui.lineEdit->setInputMask("DD");

	connect(m_ui.startButton, &QPushButton::clicked, this, &Synchronizer::OnStart);
	connect(m_ui.stopButton, &QPushButton::clicked, this, &Synchronizer::OnReset);
	
	Initialize();
}

void Synchronizer::Initialize()
{	
	auto logLeft = [this](int number)
	{
		m_ui.listWidget_left->addItem(QString::fromStdString(std::to_string(number)));
	};
	auto logRight = [this](int number)
	{
		m_ui.listWidget_right->addItem(QString::fromStdString(std::to_string(number)));
	};

	m_threadManager.Initialize(logLeft, logRight);
}

void Synchronizer::OnStart()
{
	if (m_threadManager.ThreadsInProcess())
	{
		return;
	}

	auto type = GetUserSyncType();
	auto delta = GetUserDelta();
	
	m_threadManager.Configurate(delta, type);
	m_threadManager.StartThreads();
}

void Synchronizer::OnReset()
{
	if (m_threadManager.ThreadsInProcess())
	{
		m_threadManager.TryStopThreads();
		if (m_threadManager.ThreadsInProcess())
		{
			m_threadManager.ForceStopThreads();
			QMessageBox::critical(this, windowTitle(), "Threads were terminated forcibly!");	
		}
	}

	m_ui.listWidget_left->clear();
	m_ui.listWidget_right->clear();
	m_threadManager.Reset();
}

SyncType Synchronizer::GetUserSyncType() const
{
	auto text = m_buttons->checkedButton()->text().toStdString();
	
	if (text == "no sync")
	{
		return SyncType::NO_SYNCHRONIZATION;
	}
	else if (text == "critical section")
	{
		return SyncType::CRITICAL_SECTION;
	}
	else if (text == "semaphore")
	{
		return SyncType::SEMAPHORE;
	}
	else if (text == "mutex")
	{
		return SyncType::MUTEX;
	}
	else if (text == "event")
	{
		return SyncType::EVENT;
	}

	return SyncType::NO_SYNCHRONIZATION;
}

int Synchronizer::GetUserDelta() const
{
	bool isInt = false;
	int delta = m_ui.lineEdit->text().toInt(&isInt);
	return isInt ? delta : 0;
}