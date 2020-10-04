#include "stdafx.h"
#include "Synchronizer.h"

int main(int argc, char ** argv)
{
	QApplication a(argc, argv);
	Synchronizer synchronizer;
	synchronizer.show();
	return a.exec();
}