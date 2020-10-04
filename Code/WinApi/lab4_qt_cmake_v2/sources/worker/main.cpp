#include "stdafx.h"
#include "worker.h"

int main(int argc, char ** argv)
{
	QApplication a(argc, argv);
	Worker worker;
	worker.Initialize(argc, argv);
	worker.show();
	return a.exec();
}