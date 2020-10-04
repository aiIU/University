#include "stdafx.h"

#include "WorkerGui.h"
#include "Worker.h"

WorkerGui::WorkerGui(QWidget* parent)
	: QMainWindow(parent)
	, m_worker(make_unique<ClientWorker>())
{
	m_ui.setupUi(this);

	// Установим флаги для нашего окна, чтобы кастомизировать его внешний вид
	Qt::WindowFlags flags = Qt::Window; // указываем, что эта форма будет всё-таки окном
	flags |= Qt::WindowTitleHint; //  также будет иметь заголовок
	flags |= Qt::WindowCloseButtonHint;  // добавим кнопку закрытия приложения
	flags |= Qt::MSWindowsFixedSizeDialogHint; // зафиксируем размер окна
	setWindowFlags(flags);

	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &WorkerGui::OnCheckWorkComplete);
	m_timer->setInterval(25);
}

WorkerGui::~WorkerGui()
{
	m_worker->ForceStopWork();
	LogMessage("Work has completed forcibly!");
}

bool WorkerGui::Initialize(int argc, char** argv)
{
	string errorMsg = "Incorrect command line arguments:";
	for (int i = 0; i < argc; ++i)
	{
		errorMsg += "\n" + std::to_string(i) + ". ";
		errorMsg += argv[i];
		errorMsg += ";";
	}

	if (argc != 4)
	{
		LogMessage(errorMsg);
		return false;
	}

	int workerId = std::atoi(argv[1]);
	if (workerId == 0 && argv[1][0] != '0')
	{
		LogMessage(errorMsg);
		return false;
	}

	int ttl = std::atoi(argv[2]);
	if (ttl == 0 && argv[2][0] != '0')
	{
		LogMessage(errorMsg);
		return false;
	}

	int parentId = std::atoi(argv[3]);
	if (parentId == 0 && argv[3][0] != '0')
	{
		LogMessage(errorMsg);
		return false;
	}

	string title = "Worker " + std::to_string(workerId);
	setWindowTitle(QString::fromStdString(title));

	auto onLog = [this](const string & message)
	{
		LogMessage(message);
	};
	auto onTick = [this](int ttl)
	{
		ShowTtl(ttl);
	};

	if (!m_worker->Initialize(workerId, ttl, ipc::Receiver(parentId), onLog, onTick))
	{
		LogMessage("Failed to initialize worker");
		return false;
	}

	m_timer->start();
	return true;
}

void WorkerGui::OnCheckWorkComplete()
{
	if (!m_worker->IsWorkCompleted())
	{
		return;
	}
	LogMessage("Work has completed, app will be terminate.");
	close();
}

void WorkerGui::ShowTtl(int ttl)
{
	m_ui.label_2->setText(QString::fromStdString(std::to_string(ttl)));
}

void WorkerGui::LogMessage(const string& message)
{
	sync::CriticalSectionLock lock(m_cs);
	m_ui.listWidget->addItem(QString::fromStdString(message));
}
