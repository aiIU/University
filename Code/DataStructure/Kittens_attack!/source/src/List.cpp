#include "pch.h"

#include "List.h"

void List::InsertByIndex(data_t value, int index)
{
	if (index <= Size())
	{
		m_data.insert(m_data.begin() + index, value);
	}
}

void List::RemoveByIndex(int index)
{
	if (index < Size())
	{
		m_data.erase(m_data.begin() + index);	
	}
}

int List::GetPosition(data_t value) const
{
	for (int i = 0; i < Size(); ++i)
	{
		if (m_data[i] == value)
		{
			return i;
		}
	}

	return -1;
}

void List::Clear()
{
	m_data.clear();
}

int List::Size() const
{
	return static_cast<int>(m_data.size());
}
