#include "pch.h"

#include "Tree.h"

int main()
{
	qDebug() << "Test #1 processing...";
	qDebug() << "Testing default constructor.";
	{
		auto pTree = make_unique<Tree>();
		assert(pTree);
		assert(pTree && pTree->Size() == 0 && pTree->IsEmpty());
		// pTree->Show();
	}
	qDebug() << "Test #1 completed successfully!";

	
	qDebug() << "Test #2 processing...";
	qDebug() << "Testing one insertion, one finding and one removing.";
	{
		auto pTree = make_unique<Tree>();
		for (int i = 0; i < 10; ++i)
		{
			auto value = std::rand() % 123;
			auto msg = QString("Try to insert %1...").arg(value);
			auto success = pTree->Insert(value);
			if (success)
			{
				msg += "inserted!";
			}
			else
			{
				msg += "not inserted!";
			}
			qDebug() << msg;
		}
		
		// pTree->Show();
	}
	qDebug() << "Test #2 completed successfully!";

	qDebug() << "Test #3 processing...";
	qDebug() << "Testing three insertion, three finding and three removing.";
	{
		auto pTree = make_unique<Tree>();
		for (int i = 0; i < 3; ++i)
		{
			pTree->Insert(10 * i);
			assert(pTree->Size() == i + 1 && !pTree->IsEmpty());
		}
		
		// pTree->Show();
				
		for (int i = 0; i < 3; ++i)
		{
			auto pNode = pTree->Find(10 * i);
			assert(pNode && pNode->value == 10 * i);
		}
		
		auto p0 = pTree->Find(0);
		auto p10 = pTree->Find(10);
		auto p20 = pTree->Find(20);
		assert(p10->left == p0 && p10->right == p20);		
		assert(p0->left == nullptr && p0->right == nullptr);
		assert(p20->left == nullptr && p20->right == nullptr);

		for (int i = 0; i < 3; ++i)
		{
			auto pNode = pTree->Find(10 * i);
			assert(pNode != nullptr);
			pTree->Remove(10 * i);
			assert(pTree->Size() == 2 - i);
		}
		assert(pTree->Size() == 0 && pTree->IsEmpty());
	}
	qDebug() << "Test #3 completed successfully!";

	
	qDebug() << "Testing #4.x: hardcoded tree.";
	qDebug() << "Test #4.1 processing...";
	{		
		auto pTree19 = make_unique<Tree>();
		for (int i = 0; i < 7; ++i)
		{
			pTree19->Insert(i);
		}
		// pTree19->Show();
		pTree19->Remove(6);
		// pTree19->Show();
		pTree19->Remove(5);
		// pTree19->Show();
		pTree19->Remove(4);
		// pTree19->Show();
		pTree19->Remove(3);
		// pTree19->Show();
	}
	qDebug() << "Test #4.1 completed successfully!";
	
	qDebug() << "Test #4.2 processing...";
	{		
		auto pTree19 = make_unique<Tree>();
		for (int i = 0; i < 19; ++i)
		{
			pTree19->Insert(i);
		}
		// pTree19->Show();
		for (int i = 18; i >= 0; --i)
		{
			assert(pTree19->Find(i) != nullptr);
			pTree19->Remove(i);
			assert(pTree19->Size() == i);
			// pTree19->Show();
		}
	}
	qDebug() << "Test #4.2 completed successfully!";
	
	qDebug() << "Test #5 processing...";
	qDebug() << "Testing balancing on different sets with sequentialy data numbers.";
	{
		vector<int> samples = {3, 5, 7, 19, 999, 1'000, 10'000, 100'000, 250'000};
		for (auto sample : samples)
		{
			// create new tree for every sample:
			auto pTree = make_unique<Tree>();
			for (int i = 0; i < sample; ++i)
			{
				pTree->Insert(i);
			}
			// pTree->Show();
			assert(pTree->Size() == sample);
			for (int i = sample - 1; i >= 0; --i)
			{
				assert(pTree->Find(i) != nullptr);
				pTree->Remove(i);
				assert(pTree->Size() == i);
			}
			assert(pTree->Size() == 0);
		}
	}
	qDebug() << "Test #5 completed successfully!";

	qDebug() << "Test #6 processing...";
	qDebug() << "Testing balancing on different sets with random data number.";
	{
		std::uniform_int_distribution<int> d; 
		std::random_device rd;
		
		vector<int> samples = {3, 5, 7, 19, 999, 1'000, 10'000, 100'000, 250'000};
		for (auto sample : samples)
		{
			assert(sample < std::numeric_limits<int>::max() && sample < d.max());
			qDebug() << "Sample: " << sample << "...";
			set<int> numbers;
			// create new tree for every sample:
			auto pTree = make_unique<Tree>();
			for (int i = 0; i < sample; ++i)
			{
				int __infiniteLoopGuard = 1000;
				int n;
				bool inserted;
				do
				{
					n = d(rd);
					inserted = numbers.emplace(n).second;
					__infiniteLoopGuard -= 1;
				}
				while (!inserted && __infiniteLoopGuard > 0);
				assert(__infiniteLoopGuard > 0);
				
				pTree->Insert(n);
			}
			assert(pTree->Size() == sample);
			int oldSize = pTree->Size();
			for (auto it = numbers.begin(); it != numbers.end();)
			{
				auto n = *it;
				it = numbers.erase(it);
				
				assert(pTree->Find(n) != nullptr);
				pTree->Remove(n);
				assert(pTree->Size() == oldSize - 1);
				oldSize -= 1;
			}
			assert(pTree->Size() == 0);
			qDebug() << "Sample: " << sample << " ok!";
		}
	}
	qDebug() << "Test #6 completed successfully!";
}