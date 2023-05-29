#include "lxqmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	lxQMainWindow mw;
	mw.show();

	return a.exec();
}

