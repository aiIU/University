#include "pch.h"

#include "gui/MainWindow.h"

int main(int argc, char* argv[])
{	
	QApplication app(argc, argv);

	QCommandLineParser parser;

	QCommandLineOption reactionsFileOption("reactions-file", "Path to file that contains settings of cat reactions", "reactions", ""); 
	parser.addOption(reactionsFileOption);

	parser.parse(app.arguments());
	
	MainWindow w;

	string appDir = app.applicationDirPath().toStdString();
	string reactionsFile = appDir + "/reactions.json";
	
	if (parser.isSet(reactionsFileOption))
	{
		 reactionsFile = parser.value(reactionsFileOption).toStdString();
	}
	
	w.Initialize(reactionsFile);	
	w.show();
	
	return app.exec();
}
