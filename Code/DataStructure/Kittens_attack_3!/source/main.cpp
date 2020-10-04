#include "pch.h"

#include <QApplication>
#include "gui/mainwindow.h"
#include "Tree.h"
#include "Test.h"

#ifdef TEST_MEMORY_LEAKS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

class ScopeRedirectOutput
{
public:
	ScopeRedirectOutput(std::ostream & ostream, const string & filename)
		: ostream(ostream)
	{
		out.open(filename);
		if (!out.is_open())
		{
			std::cerr << "Cannot open file!" << std::endl;
		}
		else
		{
			oldBuffer = ostream.rdbuf(); //save old buf
			ostream.rdbuf(out.rdbuf());
		}
	}
	~ScopeRedirectOutput()
	{
		ostream.rdbuf(oldBuffer);
	}
	
private:
	std::ofstream		out;
	std::ostream &		ostream;
	std::streambuf *	oldBuffer = nullptr;
};

int main(int argc, char* argv[])
{
#ifdef TEST_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	QApplication app(argc, argv);
	MainWindow w;
		
	{
		ScopeRedirectOutput redirectErrors(std::cerr, app.applicationDirPath().toStdString() + "/err.txt");
		ScopeRedirectOutput redirectOutput(std::cout, app.applicationDirPath().toStdString() + "/out.txt");
		
		InitializeTestingTools();
				
		vector<double> treeSize, operationNumber;
		
		CreateInsertionChartData(treeSize, operationNumber, 100);
		w.CreateChart(L"Вставка", treeSize, operationNumber);
		
		CreateRemovingChartData(treeSize, operationNumber, 100);
		w.CreateChart(L"Удаление", treeSize, operationNumber);
		
		CreateSearchChartData(treeSize, operationNumber, 1000);
		w.CreateChart(L"Поиск", treeSize, operationNumber);

		w.ShowChart(L"Вставка");
		w.show();
		
		DestroyTestingTools();
	}
	// std::cout << "Work has been completed. Please, press any key to exit." << std::endl;
	
	app.exec();
	
	return 0;
}
