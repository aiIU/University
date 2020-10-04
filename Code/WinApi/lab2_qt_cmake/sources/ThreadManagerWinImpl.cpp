#include "stdafx.h"
#include "ThreadManagerWinImpl.h"
#include "WinApiUtils.h"

ThreadManagerImpl::~ThreadManagerImpl()
{
	for (auto func : m_threadFunctions)
	{
		delete static_cast<std::function<void()>*>(func.paramsPtr);
	}
}

void ThreadManagerImpl::CreateThread(const std::function<void()> & userFunction)
{
	// Здесь в комментариях будут использоваться следующие обозначения:
	// 1. Пользовательная функция - функция userFunction, которую мы получаем снаружи, имеющая сигнатуру void(), то есть
	//	возвращает и принимает void
	// 2. Функция потока - функция, управление на которую будет передано потоку сразу после создания.
	//	Сигнатура функция определена WinApi - int(PVOID), т.е. принимаем void*, а возвращает int.

	WinFunc func;
	func.startFunc = [](LPVOID params) -> DWORD
	{
		// Преобразуем входные параметры (void*) в указатель на ту функцию, которую мы получили от пользователя
		auto userFuncPtr = static_cast<std::function<void()>*>(params);
		if (userFuncPtr)
		{
			auto userFunc = *userFuncPtr;
			// Исполняем эту функцию
			userFunc();	
		}
		// Высвобождаем память после исполнения функции
		return 0;
	};

	// Чтобы использовать пользовательскую функцию, мы можем передать её в качестве параметра в функцию потока.
	// Это необходимо для того, чтобы иметь возможность использовать функцию
	// с любой сигнатурой - в нашем случае void(), - а не с сигнатурой WinApi - int(LPVOID).

	// Для этого потребуется поработать с сырой памятью и создать копию пользовательской функции, 
	// которую позже обязательно нужно будет удалить.
	auto funcPtr = new std::function<void()>(userFunction);
	// Указатель на пользовательскую функция преобразуем в указатель на void, чтобы передать в функцию потока.
	func.paramsPtr = static_cast<LPVOID>(funcPtr);
	
	// Создаем поток, запуск которого мы отложим на неопределенное время, а в качестве стартовой функции укажем ранее созданную.
	auto handle = ::CreateThread(nullptr, 0, func.startFunc, func.paramsPtr, CREATE_SUSPENDED, nullptr);
	if (handle == nullptr)
	{
		LogLastError("CreateThread");
		delete funcPtr;
	}
	else
	{
		m_threadFunctions.emplace_back(std::move(func));
		m_threadHandles.push_back(handle);	
	}
}

void ThreadManagerImpl::StartThreads()
{
	for (auto handle : m_threadHandles)
	{
		ResumeThread(handle);
	}
}

bool ThreadManagerImpl::WaitThreads(int waitingTime)
{
	using namespace std::chrono;
	bool ready = true;

	// Опрашиваем каждый поток
	for (auto it = m_threadHandles.begin(); it != m_threadHandles.end();)
	{
		// Засекаем текущее время
		auto startTimePoint = high_resolution_clock::now();

		auto handle = *it;

		// Ждём завершение потока оставшееся количество времени
		auto res = WaitForSingleObject(handle, waitingTime);

		// Если поток закончил свою работу, то закрываем его хендл и удаляем из списка
		if (res == WAIT_OBJECT_0 || res == WAIT_ABANDONED)
		{
			CloseHandle(handle);
			it = m_threadHandles.erase(it);
		}
		else // Если поток еще не закончил свою работу
		{
			// Помечаем, что хотя бы один поток еще не закончил свою работу
			ready = false;
			// Если случилась ошибка во время ожидания
			if (res == WAIT_FAILED)
			{
				// Логиреуем её
				LogLastError("WaitForSingleObject");
			}
			// Идём к следующему потоку в списке
			++it;
		}

		// Засекаем сколько времени прошло на итерацию цикла
		int timeExpired = (high_resolution_clock::now() - startTimePoint).count();
		// Уменьшаем количество времени ожидания следующего потока, т.к. всё это время он честно работал
		waitingTime = std::max(0, waitingTime - timeExpired);
	}
	return ready;
}

void ThreadManagerImpl::TerminateThreads()
{
	// Опрашиваем каждый поток
	for (auto it = m_threadHandles.begin(); it != m_threadHandles.end(); )
	{
		auto handle = *it;

		// Насильно убиваем поток
		bool success = ::TerminateThread(handle, 1);
		if (!success)
		{
			// Если во время убийства потока произошла ошибка, то логируем
			LogLastError("TerminateThread");
			++it;
		}
		else
		{				
			// Закрываем хендл в случае успешного убийства
			success = ::CloseHandle(handle);
			if (!success)
			{
				// Логируем ошибку и переходим к следующему потоку
				LogLastError("CloseHandle");
				++it;
			}
			else
			{
				// В случае успешного закрытия хендла удаляем его из списка
				it = m_threadHandles.erase(it);
			}
		}
	}
}

void ThreadManagerImpl::SetErrorCallback(std::function<void(const string &)> callback)
{
	m_errorCallback = callback;
}

void ThreadManagerImpl::LogLastError(const string & functionName) const
{
	EchoErrorMessage(WinApiUtils::ErrorCodeToString(GetLastError(), functionName));
}

void ThreadManagerImpl::EchoErrorMessage(const string & error) const
{
	if (m_errorCallback && !error.empty())
	{
		m_errorCallback(error);
	}
}
