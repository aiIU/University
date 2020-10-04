#pragma once

#undef SendMessage
#undef GetMessage

namespace ipc
{	
	struct Receiver
	{
		Receiver(int id = 0) : id(id) {}

		uint32_t id {0};
	};

	enum class MessageType
	{
		// from Launcher to Worker:
		TICK = 0,
		FORCE_CLOSE,

		// from Worker to Launcher:
		RECEIVER_CHANGED,
		CLOSED,

		INVALID_MESSAGE_TYPE
	};

	class Message
	{
	public:
		Message() = default;

		// construct simple message
		Message(MessageType type, uint64_t data = 0);

		// consturct extended message
		Message(MessageType type, Receiver newReceiver, uint32_t workerId);
		
		MessageType GetType() const { return m_type; }
		uint64_t GetData() const { return m_data.simple; }

		uint32_t GetWorkerId() const;
		Receiver GetNewReceiver() const;

	private:
		union MessageData
		{
			uint64_t simple;
			struct
			{
				uint32_t workerId;
				Receiver receiver;
			} extended;
		};

		MessageType	m_type { MessageType::INVALID_MESSAGE_TYPE };
		MessageData m_data {0};
	};
	
	bool SendMessage(const Message& message, Receiver receiver);
	bool GetMessage(Message & out);
	bool WaitMessageFor(int timeout, Message & out);
}
