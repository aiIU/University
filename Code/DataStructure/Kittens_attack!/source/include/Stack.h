#pragma once

class Stack
{
public:
	using data_t = float;
	
	// Кладёт элемент value на вершину стека
	void Push(data_t value);

	// Убирает элемент с вершины стека
	void Pop();

	// Возвращает элемент, который лежит на вершине стека
	data_t Top() const;

	// Очищает стек
	void Clear();

	// Возвращает количество элементов в стеке
	int Size() const;

private:
	std::forward_list<data_t>	m_data;
	int							m_size = 0;
};