#include "pch.h"

#include "Test.h"
#include "Tree.h"

static unique_ptr<std::mt19937_64> s_generator;

constexpr static array s_samples = {
		1, 5, 10, 20, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 1250, 1500, 1750, 2000
	//1, 10, 100, 500, 1'000,
	//5'000, 10'000, 20'000, 30'000,
	//40'000, 50'000, 100'000, 250'000,
	//500'000, 750'000, 1'000'000
};

void InitializeTestingTools()
{
	std::random_device rd;
	s_generator = make_unique<std::mt19937_64>(rd());
}

void DestroyTestingTools()
{
	s_generator.reset();
}

int CreateRandomNumber(int from, int to)
{
	std::uniform_int_distribution<int> d(from, to);
	return d(*s_generator);
}

vector<int> CreateDataSet(int size)
{
	try
	{
		auto numbers = vector<int>(size, 0);
		std::iota(numbers.begin(), numbers.end(), -(size / 2));
		
		std::shuffle(numbers.begin(), numbers.end(), *s_generator);
		
		return std::move(numbers);
	}
	catch (const std::bad_alloc &)
	{
		std::cerr << "Cannot allocate enough memory!" << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cerr << "Error:" << e.what() << "!" << std::endl;
	}

	return {};
}

void CreateInsertionChartData(vector<double> & outXValues, vector<double> & outYValues, int epoch)
{
	assert(std::is_sorted(s_samples.begin(), s_samples.end(), std::less<decltype(s_samples.back())>{}));
	std::cout << "Creating insertion data..." << std::endl;

	outXValues.clear();
	for (auto sample : s_samples)
	{
		outXValues.push_back(sample);
	}
	
	auto numbers = CreateDataSet(s_samples.back());
	auto numbersIt = numbers.begin();

	outYValues.clear();
	Tree tree;
	for (auto _x : outXValues)
	{
		auto treeSize = static_cast<int>(_x);

		while (tree.Size() != treeSize)
		{
			assert(numbersIt != numbers.end());
			tree.Insert(*numbersIt);
			++numbersIt;
		}
		
		double totalY = 0.0;
		int insertedValue = 0;
		for (int i = 0; i < epoch; ++i)
		{
			if (i != 0)
			{
				tree.Remove(insertedValue);	
			}			
			tree.GetPerfomanceInfo()->Reset();

			insertedValue = CreateRandomNumber();
			tree.Insert(insertedValue);
			
			auto info = tree.GetPerfomanceInfo();		
			auto l = 0/*info->GetEnterFunctionCounter(PerfomanceHelper::LEFT_ROTATION)*/;
			auto r = 0/*info->GetEnterFunctionCounter(PerfomanceHelper::RIGHT_ROTATION)*/;
			auto f = info->GetEnterFunctionCounter(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION);
			std::cout << "l = " << l << ", r = " << r << ", f = " << f << "\n";
			
			auto y = l + r + f;
			totalY += y;
		}

		auto averageY = totalY / epoch;
		outYValues.push_back(averageY);
		
		std::cout << _x << " " << averageY << "\n";
	}
	
	std::cout << std::endl;
}

void CreateRemovingChartData(vector<double>& outXValues, vector<double>& outYValues, int epoch)
{
	assert(std::is_sorted(s_samples.begin(), s_samples.end(), std::less<decltype(s_samples.back())>{}));
	std::cout << "Creating removing data..." << std::endl;

	outXValues.clear();
	for (auto sample : s_samples)
	{
		outXValues.push_back(sample);
	}
	
	auto numbers = CreateDataSet(s_samples.back());
	auto numbersIt = numbers.begin();

	outYValues.clear();
	Tree tree;
	for (auto _x : outXValues)
	{
		auto treeSize = static_cast<int>(_x);

		while (tree.Size() != treeSize)
		{
			assert(numbersIt != numbers.end());
			tree.Insert(*numbersIt);
			++numbersIt;
		}
		
		double totalY = 0.0;
		int numberToRemove = 0;
		for (int i = 0; i < epoch; ++i)
		{
			if (i != 0)
			{
				tree.Insert(numberToRemove);
			}

			int to = std::distance(numbers.begin(), numbersIt);
			int randomIndex = CreateRandomNumber(0, to - 1);
			numberToRemove = numbers[randomIndex];
			assert(copiedTree.Find(numberToRemove) != nullptr);
			tree.GetPerfomanceInfo()->Reset();
			tree.Remove(numberToRemove);
			
			auto info = tree.GetPerfomanceInfo();		
			auto l = 0/*info->GetEnterFunctionCounter(PerfomanceHelper::LEFT_ROTATION)*/;
			auto r = 0/*info->GetEnterFunctionCounter(PerfomanceHelper::RIGHT_ROTATION)*/;
			auto f = info->GetEnterFunctionCounter(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION);
			std::cout << "l = " << l << ", r = " << r << ", f = " << f << "\n";
			
			auto y = l + r + f;
			totalY += y;
		}

		auto averageY = totalY / epoch;
		outYValues.push_back(averageY);
		
		std::cout << _x << " " << averageY << "\n";
	}
	
	std::cout << std::endl;
}

void CreateSearchChartData(vector<double>& outXValues, vector<double>& outYValues, int epoch)
{	
	assert(std::is_sorted(s_samples.begin(), s_samples.end(), std::less<decltype(s_samples.back())>{}));
	std::cout << "Creating search data..." << std::endl;

	outXValues.clear();
	for (auto sample : s_samples)
	{
		outXValues.push_back(sample);
	}
	
	auto numbers = CreateDataSet(s_samples.back());
	auto numbersIt = numbers.begin();

	outYValues.clear();
	Tree tree;
	for (auto _x : outXValues)
	{
		auto treeSize = static_cast<int>(_x);

		while (tree.Size() != treeSize)
		{
			assert(numbersIt != numbers.end());
			tree.Insert(*numbersIt);
			++numbersIt;
		}
		
		double totalY = 0.0;
		for (int i = 0; i < epoch; ++i)
		{
			int to = std::distance(numbers.begin(), numbersIt);
			int randomIndex = CreateRandomNumber(0, to - 1);
			int numberToFind = numbers[randomIndex];
			assert(copiedTree.Find(numberToFind) != nullptr);
			tree.GetPerfomanceInfo()->Reset();
			(void)tree.Find(numberToFind);
			
			auto info = tree.GetPerfomanceInfo();		
			auto f = info->GetEnterFunctionCounter(PerfomanceHelper::TOTAL_FUNCTION_EXECUTION);
			std::cout << "f = " << f << "\n";
			
			auto y = f;
			totalY += y;
		}

		auto averageY = totalY / epoch;
		outYValues.push_back(averageY);
		
		std::cout << _x << " " << averageY << "\n";
	}
	
	std::cout << std::endl;
}
