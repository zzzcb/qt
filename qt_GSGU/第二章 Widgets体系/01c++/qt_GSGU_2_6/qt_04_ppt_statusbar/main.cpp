#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MainWindow mw;
	mw.show();

    return a.exec();
}
