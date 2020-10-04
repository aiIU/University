#include "stdafx.h"
#include "LauncherGui.h"

int main(int argc, char ** argv)
{
	QApplication a(argc, argv);
	LauncherGui launcher;
	launcher.show();
	return a.exec();
}