#pragma execution_character_set("utf-8")
//#include "demo.h"
#include <QMainWindow>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Demo w;
    //w.show();

	QMainWindow* mw = new QMainWindow;
	mw->setWindowTitle("ÎÒ²»ÊÇQt");
	mw->show();

    return a.exec();
}
