#pragma once

using LogCallback = std::function<void(const string &)>;

namespace WinApi
{
	// void SendMessage();
	// void GetMessage();
	// void WaitMessage();
	string GetLastMessage(const string & functionName = {});
}

class CritSection
{
public:
	CritSection();
	~CritSection();

	void Lock();
	void Unlock();

private:
	CRITICAL_SECTION	m_crit;
};

class Worker
{
public:
	Worker();
	~Worker();

	void Start();
	void Tick();
	void Stop();

	bool IsStoped();

private:

};

class Launcher : public std::enable_shared_from_this<Launcher>
{
public:
	Launcher();
	~Launcher();

	void SetMaximumWorkers(int number);
	int GetWorkersNumber() const;

	void CreateWorker();

	std::shared_ptr<std::mt19937> GetRandom() const { return m_random; }

	void SetLogCallback(const LogCallback & callback) { m_logCallback = callback; }
	const LogCallback & GetLogCallback() const { return m_logCallback; }

private:
	struct Thread
	{
		std::thread			thread;
		std::atomic_bool	isComplete {false};
	};

	void GenerateIds();
	int GetId();
	void FreeId(int);

	// Критическая секция для синхронизации изменений из гуи, а также между внутренники потоками
	mutable CritSection		m_crit;

	// Максимальное количество рабочих, которых можно создать
	int					m_maxWorkers;
	// Массив рабочих
	vector<Worker>		m_workers;
	// Очереди свободных и занятых id
	std::queue<int>		m_freeIds;
	std::queue<int>		m_busyIds;

	/* Поток, который *в основном* будет отправлять сообщения рабочим и иногда принимать:
		1. Тик секунды (отправление)
		2. Преждевременное завершение их работы (отправление)
		3. Принятие сообщение об обмене id (принятие) */ 
	Thread				m_threadOutput;

	/* Этот поток будет принимать сообщения о прекращении работы worker-ов. */
	Thread				m_threadInput;

	/* Генератор рандомных чисел */
	std::shared_ptr<std::mt19937>	m_random;

	/* Колбэк для вывода сообщений об ошибках */
	LogCallback		m_logCallback;
};