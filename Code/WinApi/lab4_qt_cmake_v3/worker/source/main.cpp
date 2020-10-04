#include "stdafx.h"
#include "WorkerGui.h"

int main(int argc, char ** argv)
{
	QApplication a(argc, argv);
	WorkerGui worker;
	if (!worker.Initialize(argc, argv))
	{
		return 1;
	}
	worker.show();
	return a.exec();
}