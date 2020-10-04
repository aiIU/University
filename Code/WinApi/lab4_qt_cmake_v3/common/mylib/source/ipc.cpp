#include "stdafx_lib.h"
#include "ipc.h"

#include <Windows.h>
// #include <winuser.h>
// #include <memoryapi.h>
#undef SendMessage
#undef GetMessage

ipc::Message::Message(MessageType type, uint64_t data)
	: m_type(type)
{
	m_data.simple = data;
}

ipc::Message::Message(MessageType type, Receiver newReceiver, uint32_t workerId)
	: m_type(type)
{
	m_data.extended.workerId = workerId;
	m_data.extended.receiver = newReceiver;
}

uint32_t ipc::Message::GetWorkerId() const
{
	if (m_type == MessageType::RECEIVER_CHANGED)
	{
		return m_data.extended.workerId;
	}
	return static_cast<uint32_t>(m_data.simple);
}

ipc::Receiver ipc::Message::GetNewReceiver() const
{	
	if (m_type == MessageType::RECEIVER_CHANGED)
	{
		return m_data.extended.receiver;
	}
	return 0;
}

bool ipc::SendMessage(const ipc::Message& message, Receiver receiver)
{
	return PostThreadMessageA(receiver.id, WM_USER, static_cast<WPARAM>(message.GetType()), static_cast<LPARAM>(message.GetData()));
}

bool ipc::GetMessage(Message & out)
{
	return WaitMessageFor(0xFFFFFFFF, out);
}

bool ipc::WaitMessageFor(int timeout, Message& out)
{
	MSG msg;
	memset(&msg, 0, sizeof MSG);

	UINT_PTR timer = SetTimer(NULL, NULL, timeout, NULL);

	::GetMessageA(&msg, nullptr, WM_TIMER, WM_USER + 1);

	KillTimer(NULL, timer);

	if (msg.message == WM_TIMER)
	{
		return false;
	}
	
	if (msg.message == WM_USER)
	{
		auto invalidType = static_cast<WPARAM>(MessageType::INVALID_MESSAGE_TYPE);
		if (msg.wParam >= 0 && msg.wParam < invalidType)
		{
			auto type = static_cast<MessageType>(msg.wParam);
			uint64_t data = msg.lParam;
			out = Message(type, data);
			return true;
		}	
	}

	return false;
}
