//#include <QtWidgets/QApplication>
//
////#include "demo.h"
////#include "learnqtabbar.h"
//
//#include "mainwindow.h"
//
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//
//	MainWindow w;
//	w.show();
//
//    return a.exec();
//}




// one source data -> multi model
#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MainWindow mw;
	mw.show();

    return a.exec();
}
