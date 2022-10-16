#include "demo.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	Demo w;

	/**center window*/
	const QRect availableGeometry = QApplication::desktop()->availableGeometry(&w);
	w.resize(availableGeometry.width() / 2, availableGeometry.height() * 2 / 3);
	w.move((availableGeometry.width() - w.width()) / 2,
		(availableGeometry.height() - w.height()) / 2);

    w.show();
    return a.exec();
}
