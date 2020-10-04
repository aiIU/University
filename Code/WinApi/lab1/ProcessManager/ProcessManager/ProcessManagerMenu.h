#pragma once

#include "pch.h"
#include <functional>

class ProcessManager;

class ProcessManagerMenu
{
public:
	void Initialize(shared_ptr<ProcessManager> processManager);

	void Process();
private:
	void CreateProcess();

	void TerminateProcess();

	void Exit();

	static string GetUserChoice(const string & hint, bool needNewLine = true);
	static size_t GetUserChoice(size_t min, size_t max);

	weak_ptr<ProcessManager> m_processManager;

	using callback_t = std::function<void()>;
	using button_t = pair<string, callback_t>;

	vector<button_t> m_buttons;
};
