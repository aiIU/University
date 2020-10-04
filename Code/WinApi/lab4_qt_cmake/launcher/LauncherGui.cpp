#include "stdafx.h"
#include "LauncherGui.h"

LauncherGui::LauncherGui(QWidget* parent)
	: QMainWindow(parent)
	, m_forseStop(false)
{
	m_ui.setupUi(this);

	m_threadsChecker = new QTimer(this);
	m_threadsChecker->setInterval(50);
	connect(m_threadsChecker, &QTimer::timeout, this, &LauncherGui::OnCheckThreadsAlive);

	LogMessage("Application is starting.");
	m_mainLoopThread = std::thread([this]()
	{
		MainLoop();
	});
	
	m_threadsChecker->start();
}

LauncherGui::~LauncherGui()
{
	LogMessage("Application is terminating.");
	m_forseStop = true;
	m_mainLoopThread.join();
}

void LauncherGui::MainLoop()
{
	using namespace std::chrono;
	while (!m_forseStop)
	{
		if (m_childrenThreadIds.size() < GetMaxChildrenNumber())
		{
			CreateWorker();	
		}
		std::this_thread::sleep_for(seconds(1));
		for (auto && child : m_childrenThreadIds)
		{
			if (!PostThreadMessageA(child, WM_APP, static_cast<int>(Message::TICK), NULL))
			{
				auto message = GetLastError("PostThreadMessage");
				LogMessage(message, LogMessageType::LM_ERROR);
			}
			else
			{
				LogMessage("Message successfully send to " + std::to_string(child) + ".");
			}
		}
		LogMessage("Tick.");
	}

	for (auto && child : m_childrenThreadIds)
	{
		if (!PostThreadMessageA(child, WM_APP, static_cast<int>(Message::CLOSE), NULL))
		{
			auto message = GetLastError("PostThreadMessage");
			LogMessage(message, LogMessageType::LM_ERROR);
		}
	}
	m_childrenThreadIds.clear();
}

void LauncherGui::OnCheckThreadsAlive()
{
	if (m_threadInput.isComplete && m_threadOutput.isComplete)
	{
		OnThreadsComplete();
		m_threadsChecker->stop();
	}
}

void LauncherGui::OnThreadsComplete()
{
	close();
}

void LauncherGui::CreateWorker()
{
	// Ѕлокируем mutex, т.к. нам важно текущее состо€ние m_children
	// “.е. нам важно узнать id дл€ будущего worker-а, а также добавить его в список после создани€
	std::scoped_lock<std::mutex> lock(m_mutex);

	int id = m_childrenThreadIds.size() + 1;
	std::uniform_int_distribution<int> dis(3, 10);
	int ttl = dis(m_random);
	int threadId = GetCurrentThreadId();
	string commandLine = "worker.exe " + std::to_string(id) + " " + std::to_string(ttl) + " " + std::to_string(threadId);

	STARTUPINFOA sInfo;
	memset(&sInfo, 0, sizeof sInfo);
	PROCESS_INFORMATION pInfo;
	memset(&pInfo, 0, sizeof pInfo);
	BOOL result = CreateProcessA(NULL, &commandLine[0], NULL, NULL, NULL, NULL, NULL, NULL, &sInfo, &pInfo);
	if (result == TRUE)
	{
		CloseHandle(pInfo.hProcess);
		CloseHandle(pInfo.hThread);

		MSG msg;
		GetMessageA(&msg, NULL, WM_APP, WM_APP + 1);
		m_childrenThreadIds.push_back(msg.wParam);

		auto message = "Worker #" + std::to_string(id) + 
			" with thread id [" + std::to_string(msg.wParam) + 
			"] was created on " + std::to_string(ttl) + " seconds.";
		LogMessage(message, LogMessageType::LM_CREATE_WORKER);
	}
	else
	{
		auto message = GetLastError("CreateProcess");
		LogMessage(message, LogMessageType::LM_ERROR);
	}
}

void LauncherGui::LogMessage(const string& message, LogMessageType type)
{
	std::scoped_lock<std::mutex> lock(m_logMutex);

	m_ui.listWidget->addItem(QString::fromStdString(message));
	// loveyou
	auto item = m_ui.listWidget->item(m_ui.listWidget->count() - 1);
	switch (type)
	{
	case LogMessageType::LM_TEXT:
		break;
	case LogMessageType::LM_CREATE_WORKER:
		item->setTextColor(Qt::darkGreen);
		break;
	case LogMessageType::LM_ERROR:
		item->setTextColor(Qt::red);
		break;
	default:
		break;
	}
}

string LauncherGui::GetLastError(const string& functionName)
{
	return ErrorCodeToString(::GetLastError(), functionName);
}

string LauncherGui::ErrorCodeToString(DWORD code, const string & functionName)
{
	LPVOID lpMessageBuffer = nullptr;
	
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		static_cast<LPSTR>(static_cast<void*>(&lpMessageBuffer)),
		0, nullptr);

	if (!lpMessageBuffer)
	{
		return "";
	}

	auto name = functionName.empty() ? "Function" : functionName;
	auto out = name + " failed with error " + std::to_string(code) + ": " + static_cast<LPCSTR>(lpMessageBuffer);
	out.resize(out.size() - 1);
	LocalFree(lpMessageBuffer);

	return out;
}

int LauncherGui::GetMaxChildrenNumber() const
{
	return m_ui.spinBox->value();
}
