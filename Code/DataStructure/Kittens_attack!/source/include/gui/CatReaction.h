#pragma once

struct CatReaction
{
	enum class Event
	{
		// secondary reactions, like "hello!", "murrrgh" and other
		FIRST_MEETING,
		CLICK_ON_CAT,
		INACTION_TIMEOUT_SMALL_1, // небольшой таймаут, например, в 10 секунд
		INACTION_TIMEOUT_SMALL_2, // небольшой таймаут, например, в 10 секунд
		INACTION_TIMEOUT_LONG, // большой таймаут, например, в 1 минуту
		HELP_READING_START,
		HELP_READING_START_N,
		HELP_READING_END,

		// main reactions on insertion or removing
		INSERTION,
		REMOVING,
		SEACH,
		OUT_OF_RANGE_INDEX,
		INVALID_DATA,

		_COUNT
	};

	enum class Result
	{
		SUCCESSED,
		FAILED,
		IMPOSIBLE,
		
		_COUNT
	};

	enum class ContainerType
	{
		LIST,
		STACK,

		_COUNT
	};
	
	CatReaction()
	{}
	
	CatReaction(Event type)
		: event(type)
	{}
	
	CatReaction(ContainerType container, Event type)
		: container(container), event(type)
	{}
	
	CatReaction(ContainerType container, Event type, Result result)
		: event(type), container(container), result(result)
	{}

	Event			event		= Event::_COUNT;
	ContainerType	container	= ContainerType::_COUNT;
	Result			result		= Result::_COUNT;
};

inline bool operator<(CatReaction lhs, CatReaction rhs)
{
	if (lhs.event == rhs.event)
	{
		if (lhs.container == rhs.container)
		{
				return lhs.result < rhs.result;
		}
		return lhs.container < rhs.container;
	}
	return lhs.event < rhs.event;
}