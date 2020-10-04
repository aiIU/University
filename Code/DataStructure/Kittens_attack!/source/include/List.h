#pragma once

class List
{
public:
	// на роль "любого печатного символа" идеально подходит wchar_t, т.к. способен хранить русские символы
	using data_t = wchar_t;
	
	// Вставка элемента value по индексу index
	void InsertByIndex(data_t value, int index);

	// Удаление элемента по индексу index 
	void RemoveByIndex(int index);

	// Очистка всего контейнера
	void Clear();

	// Возвращает размер списка
	int Size() const;

	// Возвращает индекс искомого элемента data
	// Если элемент не найден, то возвращается -1
	int GetPosition(data_t data) const;

	// Возвращает элемент по указанному индексу.
	// По заданию не нужно, но как-то всё-таки нужно было
	// обойти весь список, чтобы занести его в таблицу
	data_t Get(int index) const { return m_data[index]; }

private:
	vector<data_t> m_data;
};