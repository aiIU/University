#include "stdafx.h"
#include "LauncherGui.h"

#include "Launcher.h"

LauncherGui::LauncherGui(QWidget* parent)
	: QMainWindow(parent)
	, m_launcher(make_unique<Launcher>())
{
	m_ui.setupUi(this);
	connect(m_ui.listWidget->model(), &QAbstractItemModel::rowsInserted, m_ui.listWidget, &QListWidget::scrollToBottom);//сигнал отправителя слот получателя

	connect(m_ui.pushButton, &QAbstractButton::clicked, this, &LauncherGui::OnButtonClick);

	LogMessage("Application is starting.");

	m_launcher->SetMaximumWorkers(GetMaxChildrenNumber());

	auto onLog = [this](const string & message)
	{
		LogMessage(message);
	};
	m_launcher->SetLogCallback(onLog);

	auto onLogError = [this](const string & message)
	{
		LogMessage(message, LogMessageType::LM_ERROR);
	};
	m_launcher->SetErrorCallback(onLogError);

	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &LauncherGui::OnTick);
	m_timer->setInterval(1000);
	m_timer->start();
}

LauncherGui::~LauncherGui()
{
	LogMessage("Application is terminating.");
}

void LauncherGui::OnButtonClick()
{
	m_onPause = !m_onPause;
	m_onPause ? OnPause() : OnContinue();
}

void LauncherGui::OnPause()
{
	m_ui.pushButton->setText(QString::fromStdString("Continue"));
	m_timer->stop();
}

void LauncherGui::OnContinue()
{
	m_ui.pushButton->setText(QString::fromStdString("Pause"));
	m_timer->start();
}

void LauncherGui::OnTick()
{
	m_launcher->SetMaximumWorkers(GetMaxChildrenNumber());
	m_launcher->Tick();
}

void LauncherGui::LogMessage(const string& message, LogMessageType type)
{
	m_ui.listWidget->addItem(QString::fromStdString(message));
	auto item = m_ui.listWidget->item(m_ui.listWidget->count() - 1);

	switch (type)
	{
	case LogMessageType::LM_TEXT:
		// item->setTextColor(Qt::green);
		break;
	case LogMessageType::LM_ERROR:
		item->setTextColor(Qt::red);
		break;
	default:
		break;
	}
}

int LauncherGui::GetMaxChildrenNumber() const
{
	return m_ui.spinBox->value();
}
