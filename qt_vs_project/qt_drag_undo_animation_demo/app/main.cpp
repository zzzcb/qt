#include "lxqdragdropwidget.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	lxQDragDropWidget w;
	w.show();


	return a.exec();
}
