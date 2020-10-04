#pragma once

struct ThreadData;

class ThreadManager
{
public:
	ThreadManager();

	~ThreadManager();

	using LogFunction = std::function<void(int)>;
	using ThreadFunction = std::function<void()>;

	void CreateThreads(std::function<LogFunction(int)> logCreator, shared_ptr<ThreadData> threadData, int threadCount = 2);

	// Создаем поток, ассоциируем с ним функцию, но не начинаем его выполнение
	void CreateThread(ThreadFunction func);

	// Начинаем выполнение всех потоков
	void StartThreads();

	// Ждём завершение работы потоков в течении указанного времени
	// Возвращается true если потоки успешно закончили свою работу
	// и false в другом случае
	bool WaitThreads(int milliseconds);

	// Насильно останавливаем потоки
	void TerminateThreads();

	bool ThreadsInProcess() const;

	void SetErrorCallback(std::function<void(const string &)> callback);

private:
	ThreadFunction CreateThreadFunction(LogFunction logger, shared_ptr<ThreadData> threadData) const;

	class ThreadManagerImpl;

	ThreadManagerImpl* m_impl;
};

class ISyncStrategy;

struct ThreadData
{
	ThreadData()
		: m_data(0), m_delta(0) {}

	volatile int				m_data;
	std::atomic_bool			m_forceStop;
	weak_ptr<ISyncStrategy>		m_sync;
	int							m_delta;
};