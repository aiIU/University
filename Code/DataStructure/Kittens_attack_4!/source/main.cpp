#include "pch.h"

#ifdef TEST_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <QApplication>
#include "gui/mainwindow.h"
#include "HashMap.h"
#include "Test.h"

int main(int argc, char* argv[])
{
#ifdef TEST_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	QApplication app(argc, argv);
	MainWindow w;
	w.show();

	InitializeTestingTools();
	
	HashTable hashTable;

	int n = s_sizeHashTable;
	int offset = 10;
	
	auto GetKey = [offset](int i)
	{
		return (offset + i) * (offset + i);
	};

	vector<double> xValues, yValues;
	xValues.push_back(0);
	yValues.push_back(0);
	
	for (int i = 0; i < n; ++i)
	{
		int key = GetKey(i);
		
		std::cout << u8"Вставка ключа " << key << u8":\n";
		hashTable.Insert(key);
		std::cout << hashTable.PrintAllData() << std::endl;

		xValues.push_back((i + 1) / double(n) * 100);
		yValues.push_back(hashTable.CollisionNumber());
	}

	w.CreateChart(L"Коллизии", L"Зависимость числа колизий (шт.) от заполненности таблицы (%)", xValues, yValues);
	
	for (int i = 0; i < n; ++i)
	{
		int key = GetKey(i);
		
		std::cerr << u8"Удаление ключа " << key << u8":\n";
		hashTable.Remove(key);		
		std::cerr << hashTable.PrintAllData() << std::endl;
	}
	
	DestroyTestingTools();

	return app.exec();
}
