#include "pch.h"

#include "Stack.h"

void Stack::Push(float value)
{
	m_data.push_front(value);
	++m_size;
}

void Stack::Pop()
{
	if (Size() == 0)
	{
		return;
	}
	
	m_data.pop_front();
	--m_size;
}

void Stack::Clear()
{
	m_data.clear();
	m_size = 0;
}

float Stack::Top() const
{
	if (Size() > 0)
	{
		return m_data.front();	
	}
	return 0;
}

int Stack::Size() const
{
	return m_size;
}
