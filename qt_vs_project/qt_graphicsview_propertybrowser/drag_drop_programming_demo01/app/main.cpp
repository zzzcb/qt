#include "lxdragdropwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	LxDragDropWidget w;
	w.show();


	return a.exec();
}
