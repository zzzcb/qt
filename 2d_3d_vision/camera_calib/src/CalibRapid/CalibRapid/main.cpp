#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	QString qss;
	QFile qssFile(":./CalibRapid.qss");
	if (qssFile.open(QFile::ReadOnly))
	{
		qss += qssFile.readAll();

		qssFile.close();
	}
	a.setStyleSheet(qss);

	MainWindow mw;
	mw.show();

    return a.exec();
}
