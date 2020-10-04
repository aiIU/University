#pragma once

constexpr int s_sizeHashTable = 10;

// Хэш таблица, в которой разрешение коллизий реализовано путем линейного зондирования.
class HashTable
{
public:	
	HashTable();

	void SetLoadFactor(float factor);
	
	void Insert(uint64_t key);
	bool Contains(uint64_t key) const;
	void Remove(uint64_t key);

	bool IsEmpty() const { return m_size == 0; }
	int Size() const { return m_size; }
	bool IsFull() const { return m_data.size() == m_size; }

	string PrintAllData() const;
	int CollisionNumber() const { return m_collisions; }
	
private:
	struct Item
	{
		Item();
		Item(Item && other) noexcept;
		Item & operator=(Item && other) noexcept;
		Item(const Item & other);
		Item & operator=(const Item & other);

		void swap(Item & other) noexcept;

		void Clear();
		
		uint64_t	key;
		bool		isEmpty;
	};
	
	void swap(Item & lhs, Item & rhs) noexcept;
	
	int hash(uint64_t key) const;
	
	const Item * FindItem(int hash, uint64_t key) const;
	Item * FindItemToModify(int hash, uint64_t key);

	array<Item, s_sizeHashTable>		m_data;
	int									m_size = 0;
	float								m_loadFactor = 0.5;
	int									m_collisions = 0;
};
