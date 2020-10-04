#include "ProcessManagerMenu.h"

#include "ProcessManager.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void ProcessManagerMenu::Initialize(shared_ptr<ProcessManager> processManager)
{
	m_processManager = processManager;

	m_buttons.emplace_back("Create process", [this]()
	{
		CreateProcess();
	});

	m_buttons.emplace_back("Terminate process", [this]()
	{
		TerminateProcess();
	});
	m_buttons.emplace_back("Terminate program", [this]()
	{
		Exit();
	});
}

void ProcessManagerMenu::Process()
{
	cout << "Simple process manager by White.\n";
	size_t n = 1;
	for (auto & button : m_buttons)
	{
		const auto & name = button.first;
		cout << n << ". " << name << "\n";
		++n;
	}
	cout << std::flush;

	const size_t exitCode = m_buttons.size();
	size_t choice = 0;
	do
	{
		choice = GetUserChoice(1, m_buttons.size() + 1);
		auto && button = m_buttons[choice - 1];
		auto && callback = button.second;
		callback();

	} while (choice != exitCode);
}

void ProcessManagerMenu::CreateProcess()
{
	if (auto processManager = m_processManager.lock())
	{
		auto && appName = GetUserChoice("Enter application name: ", false);
		try
		{
			processManager->CreateProcess(appName);
		} catch (const ProcessException & ex)
		{
			cout << ex.what() << endl;
		}
	}
}

void ProcessManagerMenu::TerminateProcess()
{
	if (auto processManager = m_processManager.lock())
	{
		auto && handlers = processManager->GetOpenProcesses();
		if (handlers.empty())
		{
			cout << "Nothing to terminate." << endl;
			return;
		}

		for (size_t i = 0; i < handlers.size(); ++i)
		{
			cout << i + 1 << ". " << handlers[i] << "\n";
		}

		size_t choice = GetUserChoice(1, handlers.size() + 1);
		try
		{
			processManager->TerminateProcess(handlers[choice - 1]);
		} catch (const ProcessException & ex)
		{
			cout << ex.what() << endl;
		}
	}
}

void ProcessManagerMenu::Exit()
{
	cout << "Good bye!" << endl;
	system("pause");
}

string ProcessManagerMenu::GetUserChoice(const string & hint, bool needNewLine /*= true*/)
{
	if (!hint.empty())
	{
		cout << hint;
		if (needNewLine)
		{
			cout << endl;
		}
	}
	string res;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(cin, res);
	return res;
}

size_t ProcessManagerMenu::GetUserChoice(size_t min, size_t max)
{
	size_t res = min;
	cout << "> ";
	cin >> res;
	while (!cin || !(res >= min && res < max))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "> ";
		cin >> res;
	}
	return res;
}
