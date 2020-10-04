#include "stdafx.h"
#include "Worker.h"

#include "WinUser.h"

Worker::Worker(QWidget* parent)
	: QMainWindow(parent)
	, m_timeToLive(0)
	, m_idWorker(-1)
	, m_isInitialized(false)
	, m_forseStop(false)
{
	m_ui.setupUi(this);

	// ”становим флаги дл€ нашего окна, чтобы кастомизировать его внешний вид
	Qt::WindowFlags flags = Qt::Window; // указываем, что эта форма будет всЄ-таки окном
	flags |= Qt::WindowTitleHint; //  также будет иметь заголовок
	flags |= Qt::WindowCloseButtonHint;  // добавим кнопку закрыти€ приложени€
	flags |= Qt::MSWindowsFixedSizeDialogHint; // зафиксируем размер окна
	setWindowFlags(flags);
	
	m_ui.listWidget->setEnabled(false);

	connect(this, &Worker::Close, this, &Worker::OnClose);

	m_mainLoopThread = std::thread([this]()
	{
		MainLoop();
	});
}

Worker::~Worker()
{
	m_forseStop = true;
	m_mainLoopThread.join();
}

void Worker::Initialize(int argc, char** argv)
{
	string error = "Incorrect command line arguments:";
	for (int i = 0; i < argc; ++i)
	{
		error += "\n" + std::to_string(i) + ". ";
		error += argv[i];
		error += ";";
	}

	if (argc != 4)
	{
		ShowErrorMessage(error);
		return;
	}

	int id = std::atoi(argv[1]);
	if (id == 0 && argv[1][0] != '0')
	{
		ShowErrorMessage(error);
		return;
	}

	int ttl = std::atoi(argv[2]);
	if (ttl == 0 && argv[2][0] != '0')
	{
		ShowErrorMessage(error);
		return;
	}

	int parentId = std::atoi(argv[3]);
	if (parentId == 0 && argv[3][0] != '0')
	{
		ShowErrorMessage(error);
		return;
	}

	HANDLE handle = m_mainLoopThread.native_handle();
	DWORD mainLoopId = GetThreadId(handle);
	LogMessage("Main Loop Thread id: " + std::to_string(std::size_t(mainLoopId)));
	if (!PostThreadMessageA(parentId, WM_APP, mainLoopId, NULL))
	{
		auto && errorMsg = GetLastError("PostThreadMessageA");
		ShowErrorMessage(errorMsg);
		return;
	}

	m_timeToLive = ttl;
	UpdateVisualTTL();

	m_idWorker = id;
	string title = "Worker " + std::to_string(m_idWorker);
	setWindowTitle(QString::fromStdString(title));

	m_parentId = parentId; 

	m_isInitialized = true;
}

void Worker::MainLoop()
{
	UINT_PTR timerId = SetTimer(NULL, NULL, 50, NULL);
	if (!timerId)
	{
		auto && error = GetLastError("SetTimer");
		ShowErrorMessage(error);
		return;
	}
	MSG msg;
	memset(&msg, 0, sizeof(MSG));
	while (auto res = GetMessageA(&msg, NULL, WM_TIMER, WM_APP + 1))
	{
		if (res == -1)
		{
			auto && error = GetLastError("GetMessage");
			ShowErrorMessage(error);
			break;
		}
		if (msg.message != WM_APP || !m_isInitialized)
		{
			continue;
		}
		
		LogMessage("CheckMessage() -> " + std::to_string(msg.message) + " - " + std::to_string(msg.wParam) + ".");
		switch (msg.wParam)
		{
		case Message::TICK:
			// ≈сли это сообщение TICK от нашего родител€, значит прошла очередна€ секунда
			// и мы выполн€ем соответствующие действи€ (обновление визуального счЄтчика
			// и закрытие при его обнулении)
			OnTick();
			break;
		case Message::CLOSE:
			// ≈сли это сообщение CLOSE от нашего родител€, значит он потребовал завершить
			// нас работу, что мы и делаем
			m_forseStop = true;
			break;
		default:
			break;
		}
		if (m_forseStop)
		{
			break;
		}
	}

	if (!KillTimer(NULL, timerId))
	{
		auto && error = GetLastError("GetMessage");
		ShowErrorMessage(error);
		return;
	}
	
	emit Close();
}

void Worker::OnTick()
{
	m_timeToLive -= 1;
	if (m_timeToLive <= 0)
	{
		OnClose();
		return;
	}
	UpdateVisualTTL();
}

void Worker::OnClose()
{
	if (!PostThreadMessageA(m_parentId, WM_APP, static_cast<int>(Message::CLOSE), NULL))
	{
		auto && err = GetLastError("PostThreadMessage");
		ShowErrorMessage(err);
	}
	LogMessage("Worker is terminating.");
}

void Worker::UpdateVisualTTL()
{
	m_ui.label_2->setText(QString::fromStdString(std::to_string(m_timeToLive)));
}

void Worker::LogMessage(const string& message)
{
	m_ui.listWidget->addItem(QString::fromStdString(message));
}

void Worker::ShowErrorMessage(const string & message)
{
	QMessageBox::critical(this, windowTitle(), QString::fromStdString(message));
}

string Worker::GetLastError(const string& functionName)
{
	return ErrorCodeToString(::GetLastError(), functionName);
}

string Worker::ErrorCodeToString(DWORD code, const string & functionName)
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
	LocalFree(lpMessageBuffer);

	return out;
}

