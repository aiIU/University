#include "stdafx.h"
#include "lab2_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	lab2_qt w;
	w.show();
	return a.exec();
}
