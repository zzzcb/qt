#include "demo.h"
#include <QApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("ZCB");
	QCoreApplication::setApplicationName("Rich Text");
	QCoreApplication::setApplicationVersion("0.0.1");
	
	/**1. arg parser*/
	QCommandLineParser parser; 
	parser.setApplicationDescription("Usage: prog.exe [option]");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The file to open.");
	parser.process(app);

	Demo w;
	/**2. center mainwindow*/
	const QRect availableGeometry = QApplication::desktop()->availableGeometry(&w);
	w.resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
	w.move((availableGeometry.width() - w.width()) / 2, (availableGeometry.height() - w.height()) / 2);

	if (!w.load(parser.positionalArguments().value(0, ":/example.html")))
		w.newFile();

    w.show();

    return app.exec();
}
