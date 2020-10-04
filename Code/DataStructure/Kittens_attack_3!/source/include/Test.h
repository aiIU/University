#pragma once

// Инициализация внутренних переменных
void InitializeTestingTools();

// Деинициализация внутренних переменных
void DestroyTestingTools();

// Создаём случайное число в указанном диапазоне
int CreateRandomNumber(int from = std::numeric_limits<int>::min(), int to = std::numeric_limits<int>::max());

// Создаём массив случайных чисел (от -size/2 до +size/2) указанного размера
vector<int> CreateDataSet(int size);

// Зависимость количества операций вставки от размера дерева, т.е.
//		X - размер дерева
//		Y - количество рекурсивных вызовов вставки для вставки одного элемента
void CreateInsertionChartData(vector<double> & outXValues, vector<double> & outYValues, int epoch);

// Зависимость количества операций удаления от размера дерева, т.е.
//		X - размер дерева
//		Y - количество рекурсивных вызовов удаления для удаления одного элемента
void CreateRemovingChartData(vector<double> & outXValues, vector<double> & outYValues, int epoch);

// Зависимость количества операций поиска от размера дерева, т.е.
//		X - размер дерева
//		Y - количество рекурсивных вызовов поиска для поиска одного элемента
void CreateSearchChartData(vector<double> & outXValues, vector<double> & outYValues, int epoch);