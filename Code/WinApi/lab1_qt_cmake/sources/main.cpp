#include "stdafx.h"

#include "lab1_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	lab1_qt w;
	w.show();
	return a.exec();
}
