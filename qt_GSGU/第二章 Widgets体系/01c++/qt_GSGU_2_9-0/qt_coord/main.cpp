#include "lxqcircle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	lxQCircle circle;
	circle.show();

    return a.exec();
}
